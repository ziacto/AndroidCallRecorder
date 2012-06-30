#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/cdefs.h>
#include "alsa_sock.h"

void usage() {
    fprintf(stderr,"Invalid arguments. Please specify a command:\n"
#ifdef DEBUG_CONTEXTS
        "list\t\tlist active recording contexts\n"
#endif
        "dev <name>\tset device name to <name>\n"
        "cfg <file>\tset config file to <file> (full path needed!)\n"
        "start <file>\tstart recording to <file>\n"
#ifdef DEBUG_CONTEXTS
        "stop [address]\tstop recording context at <address>, or all contexts no address given\n"
#else
        "stop <address>\tstop recording context at <address>\n"
#endif
        "load\t\tload config file\n"
        "info\t\tshow current device and config file names\n"
    );
    exit(0);
}



int main(int argc, char **argv) {

     int   alsa_sock = -1, alsa_req = -1, ret;
     void *ctx = 0;
     struct sockaddr_un srv;
     char *file = 0, *dev = 0;	
     char buf[1024];

#ifdef DEBUG_CONTEXTS
	if(argc == 2 && strcmp(argv[1],"list") == 0) alsa_req = ALSA_LIST;
	else if(argc == 2 && strcmp(argv[1],"stop") == 0) alsa_req = ALSA_STOP_ALL;
	else
#endif
	if(argc == 2 && strcmp(argv[1],"load") == 0) alsa_req = ALSA_LOAD_CFG;
	else if(argc == 2 && strcmp(argv[1],"info") == 0) alsa_req = ALSA_SHOW_CFG;
	else if(argc != 3) usage();
	else if(strcmp(argv[1],"start") == 0) {
	    file = argv[2];	
	    alsa_req = ALSA_START_REC; 	
	} else if(strcmp(argv[1],"stop") == 0) {
	    if(sscanf(argv[2],"%p",&ctx) != 1) usage();
	    alsa_req = ALSA_STOP_REC;	
	} else if(strcmp(argv[1],"dev") == 0) {
	    dev = argv[2];
	    alsa_req = ALSA_DEV_NAME;	
	} else if(strcmp(argv[1],"cfg") == 0) {
	    file = argv[2];
	    alsa_req = ALSA_MIX_FILE;		
	} else usage();

	alsa_sock = socket(AF_UNIX, SOCK_SEQPACKET, 0);
	if(alsa_sock < 0) {
	    fprintf(stderr, "cannot create socket\n");
	    return 1;	
	}
	srv.sun_family = AF_UNIX;
	strcpy(srv.sun_path,ASOCK_NAME);

	if(connect(alsa_sock, (struct sockaddr *)&srv, sizeof(struct sockaddr_un)) != 0) {
	    fprintf(stderr, "cannot connect to socket\n");	
	    goto fail;
	}
	if(write(alsa_sock, &alsa_req, 4) != 4) {
	    fprintf(stderr, "cannot send cmd to socket\n");	
	    goto fail;
	}
	switch(alsa_req) {
	    case ALSA_START_REC:
		fprintf(stderr, "sending ALSA_START_REC: file=%s\n", file);
                if(write(alsa_sock, file, strlen(file)+1) != strlen(file)+1) {
                    fprintf(stderr, "cannot file name to socket\n");
		    goto fail;
                }
                if(read(alsa_sock, &ctx, 4) != 4) {
                    fprintf(stderr, "ALSA_START_REC: no response from server\n");
		    goto fail;	
                }
		if(ctx) fprintf(stderr, "Recording started, address to stop: %p\n", ctx);
		else fprintf(stderr, "Recording NOT started.\n");
		break;	
	    case ALSA_STOP_REC:
		if(write(alsa_sock, &ctx, 4) != 4) {
		    fprintf(stderr, "cannot send stop/kill context to socket\n");	
		    goto fail;
		}
		fprintf(stderr, "stop request sent, context=%p\n", ctx);
                if(read(alsa_sock, &ret, 4) != 4) {
                    fprintf(stderr, "ALSA_STOP_REC: no response from server\n");
                    goto fail;
                }
		if(ret) fprintf(stderr, "Stopped.\n");
		else fprintf(stderr, "Invalid context.\n");
		break;
	    case ALSA_DEV_NAME:
		if(write(alsa_sock, dev, strlen(dev)+1) != strlen(dev)+1) {
		    fprintf(stderr, "cannot device name to socket\n");	
		    goto fail;	
		}
		if(read(alsa_sock, &ret, 4) != 4) {
		    fprintf(stderr, "ALSA_DEV_NAME: no response from server\n");	
		    goto fail;	    
		}
		fprintf(stderr, "%s\n", ret ? "OK":"Error");
		break;
#ifdef DEBUG_CONTEXTS
	    case ALSA_LIST:
		for(ret = 0; read(alsa_sock, &ctx, 4) == 4; ret++) 
			fprintf(stderr, "Active context %d: %p\n", ret, ctx);	
		if(ret == 0) fprintf(stderr, "No active contexts.\n");
		break;	
	    case ALSA_STOP_ALL:
		if(read(alsa_sock, &ret, 4) != 4) {
		    fprintf(stderr, "ALSA_STOP_ALL: no response from server\n");
	 	    goto fail;
        }
		if(!ret) fprintf(stderr,"Nothing stopped\n");
		else fprintf(stderr, "Stopped %d context%s\n", ret, ret == 1 ? "" : "s");
		break;
#endif
            case ALSA_MIX_FILE:
                if(write(alsa_sock, file, strlen(file)+1) != strlen(file)+1) {
                    fprintf(stderr, "cannot device name to socket\n");
                    goto fail;
                }
                if(read(alsa_sock, &ret, 4) != 4) {
                    fprintf(stderr, "ALSA_MIX_FILE: no response from server\n");
                    goto fail;
                }
                fprintf(stderr, "%s\n", ret ? "OK":"Error");
		break;
	    case ALSA_LOAD_CFG:
		if(read(alsa_sock, &ret, 4) != 4) {
                    fprintf(stderr, "ALSA_LOAD_CFG: no response from server\n");
                    goto fail;
                }
                if(!ret) fprintf(stderr,"Load failed, please check config file path.\n");
                fprintf(stderr, "Mixer config file loaded\n");
                break;
            case ALSA_SHOW_CFG:
                if(read(alsa_sock, buf, sizeof buf) <= 0) {
                    fprintf(stderr, "ALSA_SHOW_CFG: no response from server\n");
                    goto fail;
                }
		fprintf(stderr,"Current config: %s\n", buf);
		break;
	    default:
		fprintf(stderr, "invalid command\n");
		break;
	}
	close(alsa_sock);
	return 0;
    fail:
	close(alsa_sock);
	return 1;	
}





