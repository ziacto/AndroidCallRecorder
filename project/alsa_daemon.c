#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <limits.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/cdefs.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <android/log.h>

#define _POSIX_C_SOURCE

#include "alsa/asoundlib.h"
#include "alsa_sock.h"

#ifdef USE_TINYALSA
#include "alsa/tinyalsa.h"
#define ALSA_CONFIG_FILE  FILES_PATH "live.cfg"
#define ALSA_DEVICE	"plughw:0,1"
#else
#define ALSA_CONFIG_FILE  FILES_PATH "live.conf"
#define ALSA_DEVICE	"plughw:0,0"
#endif

#define ALSA_DEV_FILE_PATH	FILES_PATH "device.cfg"

#define TAG_NAME	"voix_alsa_daemon"
#define log_info(fmt, args...)  __android_log_print(ANDROID_LOG_INFO, TAG_NAME, "[%s] " fmt, __func__, ##args)
#define log_err(fmt, args...)   __android_log_print(ANDROID_LOG_ERROR, TAG_NAME, "[%s] " fmt, __func__, ##args)

static char *alsa_device = 0;
static char *alsa_config_file = 0;
static pthread_mutex_t mutty;
static void do_mixer_settings(FILE *file);

static int alsa_set_device(char *dev) {
    int ret = 1;
	pthread_mutex_lock(&mutty);
	log_info("set_device");
	if(dev && *dev) {
	    if(alsa_device) free(alsa_device);
	    alsa_device = strdup(dev);
	    if(!alsa_device) {
		log_err("no memory");
		ret = 0;
	    } else log_info("alsa device set to %s", alsa_device);	
	} else {
	    log_err("invalid string passed");
	    ret = 0;	
	}
	pthread_mutex_unlock(&mutty);
    return ret;
}

static int alsa_set_config_file(char *file) {
    if(!file || !*file) {
	log_err("invalid parameter");
	return 0;
    }	
    if(alsa_config_file) free(alsa_config_file);
    alsa_config_file = strdup(file);
    if(!alsa_config_file) {
	log_err("no menory");
	return 0;	
    }
    return 1;	
}

static void *record(void *);

typedef struct {
    snd_pcm_t *snd;	/* alsa handle */	
    int	fd_out;		/* file being recorded */
    char *cur_file;	/* its full path */
    pthread_t rec;	/* recording thread */
    char *buff;		/* read buffer */
    int frames;         /* its size in frames */    
    int running;	/* context running */	
} rec_ctx;


#ifdef DEBUG_CONTEXTS
/* Max number of calls recorded in parallel. Debug only restriction. */
#define MAX_CTX		8
static rec_ctx *contexts[MAX_CTX];
#endif

static int init_recording(rec_ctx *ctx);

static void free_ctx(rec_ctx *ctx) {
    if(!ctx) return;	
    if(ctx->cur_file) free(ctx->cur_file);
    if(ctx->buff) free(ctx->buff);
    free(ctx);
}

static void *start_record_alsa(char *file) {

    pthread_attr_t attr;
    const char *folder = 0;
    struct stat st;
    rec_ctx *ctx = 0;
#ifdef DEBUG_CONTEXTS
    int ctx_idx;
#endif
	pthread_mutex_lock(&mutty);
	log_info("start_record");

#ifdef DEBUG_CONTEXTS
	for(ctx_idx = 0; ctx_idx < MAX_CTX; ctx_idx++) if(!contexts[ctx_idx]) break;
	if(ctx_idx == MAX_CTX) {
	    log_err("no free contexts");
	    return 0;		
	}
#endif
	ctx = (rec_ctx *) calloc(sizeof(rec_ctx),1);
	if(!ctx) {
	    log_err("no memory!");
	    goto fail;
	}

	ctx->fd_out = -1; 

	ctx->cur_file = (char *) malloc(strlen(file)+1);
	if(!ctx->cur_file) {
            log_err("no memory!");
	    goto fail;	
        }
	strcpy(ctx->cur_file,file);

	/* Open/configure the device, and open output file */	

	if(!init_recording(ctx)) goto fail;
	
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	pthread_create(&ctx->rec,&attr,record,ctx);
	log_info("started recording to %s (ctx=%p)", file, ctx);

	pthread_attr_destroy(&attr);
	pthread_mutex_unlock(&mutty);
#ifdef DEBUG_CONTEXTS
	contexts[ctx_idx] = ctx;
#endif
	return ctx;

    fail:
	free_ctx(ctx);
	pthread_mutex_unlock(&mutty);

	return 0;
}


/*  Called from start_record() only. Device is closed on error (if it was opened). 
    Two variants of this function, depending on the library we're linking with.
*/


static int init_recording(rec_ctx *ctx) {

    int err;
    snd_pcm_hw_params_t *hw_params = 0;
    snd_pcm_uframes_t frames = 512;
    struct stat st;

	if(stat(alsa_config_file, &st) == 0) {
	     if(strstr(alsa_config_file, ".conf")) {	
		char *cmd = malloc(strlen(alsa_config_file)+strlen(ALSA_CTL_CMD)+32);	
		sprintf(cmd, "%s -f %s restore", ALSA_CTL_CMD, alsa_config_file);	
		if(system(cmd) == -1) log_err("failed to execute alsa_ctl");
		else log_info("live recording configuration loaded");
		free(cmd);
	     } else {
		FILE *file = fopen(alsa_config_file, "r");
		if(file) {
		    do_mixer_settings(file);
		    fclose(file);
		} else log_err("failed to open %s", alsa_config_file);
	     }	
	} else log_info("%s not found, skipped loading live config", alsa_config_file);

	if((err = snd_pcm_open(&ctx->snd, alsa_device, SND_PCM_STREAM_CAPTURE, 0)) < 0) {
	     log_err("cannot open audio device %s (%s)", alsa_device, snd_strerror(err));
	     return 0;
	}
	if((err = snd_pcm_hw_params_malloc(&hw_params)) < 0) {
	     log_err("cannot allocate hardware parameter structure (%s)\n", snd_strerror(err));
	     goto fail;		     	
	}
	if((err = snd_pcm_hw_params_any(ctx->snd, hw_params)) < 0) {
	     log_err("cannot initialize hardware parameter structure (%s)\n", snd_strerror(err));
	     goto fail;		     	
	}
	if((err = snd_pcm_hw_params_set_access(ctx->snd, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0) {
	     log_err("cannot set access type (%s)\n", snd_strerror(err));
	     goto fail;		     	
	}
	if((err = snd_pcm_hw_params_set_format(ctx->snd, hw_params, SND_PCM_FORMAT_S16_LE)) < 0) {
	     log_err("cannot set sample format (%s)\n", snd_strerror(err));
	     goto fail;		     	
	}
	if((err = snd_pcm_hw_params_set_rate(ctx->snd, hw_params, 8000, 0)) < 0) {
	     log_err("cannot set sample rate (%s)\n", snd_strerror(err));
	     goto fail;		     	
	}
	if((err = snd_pcm_hw_params_set_channels(ctx->snd, hw_params, 1)) < 0) {
	     log_err("cannot set channel count (%s)\n", snd_strerror(err));
	     goto fail;		     	
	}
	if((err = snd_pcm_hw_params_set_period_size(ctx->snd, hw_params, frames, 0)) < 0) {
	     log_err("cannot set period size (%s)\n", snd_strerror(err));
#if 0
	     goto fail;
#endif		     	
	}
	if((err = snd_pcm_hw_params(ctx->snd, hw_params)) < 0) {
	     log_err("cannot set parameters (%s)\n", snd_strerror(err));
	     goto fail;		     	
	}
	snd_pcm_hw_params_free(hw_params);
	hw_params = 0;
	ctx->frames = frames;
	ctx->buff = (char *) malloc(frames * 2);
	if(!ctx->buff) {
	     log_err("out of memory, size requested = %ld", frames*2);
	     goto fail;		
	}	
	if((err = snd_pcm_prepare(ctx->snd)) < 0) {
	     log_err("cannot prepare audio interface for use (%s)\n", snd_strerror(err));
	     goto fail;		     	
	}
	ctx->fd_out = open(ctx->cur_file,O_CREAT|O_TRUNC|O_WRONLY, 0666);
	if(ctx->fd_out < 0) {
	    log_err("cannot open output file \'%s\'", ctx->cur_file); 
	    goto fail;
	}
	return 1;

   fail:
	if(hw_params) snd_pcm_hw_params_free(hw_params);
	if(ctx->snd) snd_pcm_close(ctx->snd);
	return 0;
}



/*  Main recording thread. */

static void *record(void *context) {

    int i, err;	
    rec_ctx *ctx = (rec_ctx *) context;

	log_info("entering recording thread");

	if((err = snd_pcm_start(ctx->snd)) < 0) {
	     log_err("cannot start recording (%s)", snd_strerror(err));		
	}

#define MAX_ERR_COUNT 3
	err = 0;
	ctx->running = 1;
	while(ctx->running) {
	    if(!ctx->snd) {
		log_info("closed from outside");
		break;
	    }		
	    i = snd_pcm_readi(ctx->snd, ctx->buff, ctx->frames);
	    if(i == -EPIPE) {	
		log_info("overrun in recording thread");
		snd_pcm_prepare(ctx->snd);
		continue;
	    } 
	    if(i < 0) { 
		err++;
		log_info("read error (%s), snd=%d", snd_strerror(i), ctx->snd);
		if(err == MAX_ERR_COUNT) {
		    log_err("max read err count in recording thread reached");
		    break;
		}
	    } else if(i <= ctx->frames) {
		if(i != ctx->frames) {
		    log_info("short read (%d frames) from alsa", i);	
		    if(i == 0) continue;	
		}
		i = write(ctx->fd_out, ctx->buff, i*2);
		if(i < 0) {
		    if(ctx->fd_out == -1) break;	
		    log_info("write error in recording thread");
		    break;
		}
	    } else log_err("this cannot happen");
	}
	if(ctx->fd_out >= 0) close(ctx->fd_out);
	log_info("exiting recording thread");

    return 0;
}

static int stop_record_alsa(void *context) {

    pthread_t k;
    rec_ctx *ctx = (rec_ctx *) context;
#ifdef DEBUG_CONTEXTS
    int ctx_idx;
#endif
        if(!ctx) {
            log_err("zero context");
            return 0;
        }
#ifdef DEBUG_CONTEXTS
        for(ctx_idx = 0; ctx_idx < MAX_CTX; ctx_idx++) if(contexts[ctx_idx] == ctx) break;
        if(ctx_idx == MAX_CTX) {
            log_err("no such context");
            return 0;
        }
	contexts[ctx_idx] = 0;
#endif
	pthread_mutex_lock(&mutty);
	log_info("stop_record (ctx=%p)", ctx);
	ctx->running = 0;
        pthread_join(ctx->rec,0);
	log_info("recording thread stopped");
	if(ctx->snd) snd_pcm_close(ctx->snd);
        free_ctx(ctx);
	pthread_mutex_unlock(&mutty);
    return 1;	
}


#include <dirent.h>

static void kill_running_copies(const char *proc_name) {

    DIR *dir;
    struct dirent *d;
    int  pid, fd;
    char tmp[256];

	dir = opendir("/proc");
	while((d = readdir(dir)) != 0) {
	    pid = atoi(d->d_name);
	    if(pid <= 0 || pid > 65535) continue;
	    if(pid == getpid())	continue; /* it's me */
	    sprintf(tmp,"/proc/%s/cmdline", d->d_name);
	    if((fd = open(tmp, O_RDONLY)) < 0) continue;
	    read(fd, tmp, 256);
	    close(fd);
	    if(strcmp(tmp, proc_name) == 0) {
		log_info("killing my copy pid=%d", pid);
		kill(pid, SIGKILL);
	    }	
	}
	closedir(dir);
}

static void terminate(int sig) {
     if(alsa_config_file) free(alsa_config_file);
     if(alsa_device) free(alsa_device);
}

int main(int argc, char **argv) {

     pid_t pid;
     int  i, k, alsa_sock, asock, alsa_req;
     void *ctx;
     struct sockaddr_un srv;
     char buff[1024];
     struct stat st;
     int dev_unknown = 1;	

	alsa_config_file = strdup(ALSA_CONFIG_FILE);

	if(stat(ALSA_DEV_FILE_PATH, &st) == 0) {
	    FILE *f = fopen(ALSA_DEV_FILE_PATH, "r");		
		if(f && fgets(buff, sizeof(buff),f)) {
		     char *c = strchr(buff,'\n');
		     if(c) *c = 0;
		     alsa_device = strdup(buff);
		     dev_unknown = 0;
		}
		if(f) fclose(f);
	} 
	if(dev_unknown) alsa_device = strdup(ALSA_DEVICE);

	kill_running_copies(argv[0]);

        pid = fork();
        if(pid < 0) {
            log_err("cannot fork daemon process");
            return 1;
        } else if(pid != 0) {
            log_info("Started daemon, pid=%d", pid);
            fprintf(stderr, "daemon started, pid=%d\n", pid);
            return 0;
        }
        pid = setsid();
        if(pid < 0) {
            log_err("cannot start new session");
            return 1;
        }
        pthread_mutex_init(&mutty,0);

	alsa_sock = socket(AF_UNIX, SOCK_SEQPACKET, 0);
	if(alsa_sock < 0) {
	    log_err("cannot create socket");
	    return 1;	
	}
	srv.sun_family = AF_UNIX;
	strcpy(srv.sun_path,ASOCK_NAME);

#if 0
        if(connect(alsa_sock, (struct sockaddr *)&srv, sizeof(struct sockaddr_un)) == 0) {
            log_err("daemon already loaded\n");
            close(alsa_sock);
            return 1;
        }
#endif

	unlink(ASOCK_NAME);
	if(bind(alsa_sock, (struct sockaddr *)&srv, sizeof(struct sockaddr_un)) != 0) {
	    log_err("cannot bind to socket");	
	    return 1;
	}

	signal(SIGHUP, terminate);

	listen(alsa_sock,1);	
        log_info("started listening on %s", srv.sun_path);

	while(alsa_sock >= 0) {
	    asock = accept(alsa_sock,0,0);	
	    if(asock < 0) {
		log_err("failed to accept new request");
		continue;
	    }
	    if(read(asock, &alsa_req, 4) != 4) {
		log_err("cannot read client request type");
		close(asock);
		continue;
	    }  	
	    log_info("processing request, type = %d", alsa_req);
	    switch(alsa_req) {
		case ALSA_DEV_NAME:
		    if(read(asock, buff, sizeof(buff)) <= 0) {
			log_err("cannot read device name");
			break;
		    }		
		    k = alsa_set_device(buff);
		    if(write(asock, &k, 4) != 4) log_err("failed to respond to client");
		    break;		
		case ALSA_START_REC:
		    if(read(asock, buff, sizeof(buff)) <= 0) {
			log_err("cannot read file name");
			break;
		    }
		    ctx = start_record_alsa(buff);
		    if(write(asock, &ctx, 4) != 4) log_err("failed to respond to client");
		    break;
		case ALSA_STOP_REC:
		    if(read(asock, &ctx, 4) != 4) {
			log_err("cannot read context");
			break;
		    } 		
		    k = stop_record_alsa(ctx);
		    if(write(asock, &k, 4) != 4) log_err("failed to respond to client");
		    break;	
#ifdef DEBUG_CONTEXTS
		case ALSA_STOP_ALL:
		    for(i = 0, k = 0; i < MAX_CTX; i++) 
			if(contexts[i]) k += stop_record_alsa(contexts[i]); 
		    if(write(asock, &k, 4) != 4) log_err("failed to respond to client");
		    break;
#endif	
		case ALSA_PING:
		    if(read(asock, buff, 4) != 4) {
			log_err("cannot read client value");
			break;
		    }
		    if(write(asock, buff, 4) != 4) log_err("cannot echo client value");
		    break;	
#ifdef DEBUG_CONTEXTS
		case ALSA_LIST:
		    for(k = 0; k < MAX_CTX; k++)	
			if(contexts[k] && write(asock, &contexts[k], 4) != 4) {
			    log_err("cannot write to client");
			    break;
			}
		    break;	
#endif			
                case ALSA_MIX_FILE:
                    if(read(asock, buff, sizeof(buff)) <= 0) {
                        log_err("cannot read mixer config file name");
                        break;
                    }
                    k = alsa_set_config_file(buff);
                    if(write(asock, &k, 4) != 4) log_err("failed to respond to client");
                    break;
		case ALSA_LOAD_CFG:
		    {	
			FILE *file = fopen(alsa_config_file, "r");
			k = 0;
			if(file) {
			    do_mixer_settings(file);
			    k = 1;	
			    fclose(file);
			}
			if(write(asock, &k, 4) != 4) log_err("failed to respond to client");
		    } 	
		    break;	
		case ALSA_SHOW_CFG:
		    sprintf(buff, "dev=%s config=%s", alsa_device, alsa_config_file);
		    k = strlen(buff);
		    if(write(asock, buff, k) != k) log_err("failed to respond to client");			   	 	
		    break;	
		default:
		    log_err("invalid request %d from client", alsa_req);
		    break;		
	    }		
	    close(asock);	
	}

     return 0;	
}

/* Valid line format of cfg file is: "[SP*]name[SP*]<TAB>[SP*]value[SP*]", where:
"name" may not start with '#' (the line is considered a comment otherwise),
[SP*] -- optional spaces (including tabs),
"name" and "value" may have spaces inside (excluding tabs). */

static int parse_config_line(char *string, char **name, char **value) {
    char *c = string, *ce;
	while(*c && isspace(*c)) c++;
	if(*c == 0 || *c == '#') return 0;
	*name = c;  /* neither space nor # */
	while(*c && *c != '\t')	c++;
	if(*c != '\t') return 0; /* no tabs in string*/
	for(ce = c++; isspace(*ce); ce--) ;
	*(ce + 1) = 0;
	while(*c && isspace(*c)) c++;
	if(*c == 0) return 0;	/* no non-space chars after tab */
	*value = c; /* not space */
	while(*c) c++;
	for(ce = --c; isspace(*ce); ce--) ;
	if(ce != c) *(ce + 1) = 0;
    return 1;	
}

#ifdef USE_TINYALSA
static void tinymix_set_value(struct mixer *mixer, char *name, char *value)
{
    struct mixer_ctl *ctl;
    enum mixer_ctl_type type;
    unsigned int i, num_values;

    ctl = mixer_get_ctl_by_name(mixer, name);
    if(!ctl) {
        log_err("cannot find control \'%s\'", name);
        return;
    }
    type = mixer_ctl_get_type(ctl);
    num_values = mixer_ctl_get_num_values(ctl);

    if(isdigit(value[0])) {
        int val = atoi(value);
        for(i = 0; i < num_values; i++) {
            if(mixer_ctl_set_value(ctl, i, val)) {
		log_err("value %d not accepted for %s", val, name);
		return;
            }
        }
    } else if(type == MIXER_CTL_TYPE_ENUM) {
        if(mixer_ctl_set_enum_by_string(ctl, value))
            log_err("value %s not accepted for %s", value, name);
    } else if(type == MIXER_CTL_TYPE_BOOL) {
        if(strcasecmp(value,"on") == 0) i = 1;
        else if(strcasecmp(value, "off") == 0) i = 0;
        else {
            log_err("cannot set %s to \'%s\', on/off or 1/0 expected", name, value);
            return;
        }
        if(mixer_ctl_set_value(ctl, 0, i)) log_err("value %d not accepted for %s", i, name);
    } else log_err("type mismatch for %s, ignored", name);
}

static void do_mixer_settings(FILE *file) {

    struct mixer *mixer;
    char buf[256], *name, *value;

    mixer = mixer_open(0);
    if(!mixer) {
        log_info("cannot open mixer");
        return;
    }
    log_info("processing mixer settings from %s", alsa_config_file);
    while(fgets(buf, sizeof(buf),file)) {
	if(parse_config_line(buf, &name, &value)) {
	   log_info("%s -> %s", name, value);
           tinymix_set_value(mixer, name, value);
	}
    }
    mixer_close(mixer);
    log_info("mixer settings processed");
}
#else
static void do_mixer_settings(FILE *file) {

    char buf[256], cmd[256], *name, *value;
    int  i, pp[2], pid;
    char *argv[] = {ALSA_MIX_CMD, "-s", "-q", 0};

    log_info("processing mixer settings from %s", alsa_config_file);

    pipe(pp);
    signal(SIGPIPE, SIG_IGN);
    signal(SIGCHLD, SIG_IGN);
    pid = fork();	
    if(pid < 0) {
	log_err("fork failed");
	return;
    }	
    if(pid == 0) {
	dup2(pp[0],0);
	close(pp[1]); close(pp[0]);
	execv(ALSA_MIX_CMD, argv);
	return; /* mustn't be reached */
    }
    close(pp[0]);
    while(fgets(buf, sizeof(buf),file)) {
	if(parse_config_line(buf, &name, &value)) {
	    log_info("%s -> %s", name, value);
	    sprintf(cmd, "cset name=\"%s\" \"%s\"\n", name, value);	
	    i = strlen(cmd);	
	    if(write(pp[1], cmd, i) != i) {
		log_err("write error\n");
		break;
	    }	
	}
    }   
    close(pp[1]);
    waitpid(pid,0,0);
    signal(SIGPIPE, SIG_DFL);
    signal(SIGCHLD, SIG_DFL);

    log_info("mixer settings processed");
}
#endif






