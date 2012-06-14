/**
 * pcm2wav.c 
 * add wav head for pcm data
 */

#include <stdio.h>
#include <string.h>

//wav头的结构如下所示：  
typedef   struct   {  
    char         fccID[4];        
    unsigned   long       dwSize;            
    char         fccType[4];    
}HEADER;  

typedef   struct   {  
    char         fccID[4];        
    unsigned   long       dwSize;            
    unsigned   short     wFormatTag;    
    unsigned   short     wChannels;  
    unsigned   long       dwSamplesPerSec;  
    unsigned   long       dwAvgBytesPerSec;  
    unsigned   short     wBlockAlign;  
    unsigned   short     uiBitsPerSample;  
}FMT;  

typedef   struct   {  
    char         fccID[4];          
    unsigned   long       dwSize;              
}DATA;  

void show_usage()
{
    printf("PCM 2 WAV usage\n eg:pcm2wav pcm_file wav_file channels sample_rate bits\n");
}

int main(int argc, char **argv)
{
    char src_file[128] = {0};
    char dst_file[128] = {0};
    int channels = 1;
    int bits = 16;
    int sample_rate = 22050;

    //以下是为了建立.wav头而准备的变量  
    HEADER   pcmHEADER;  
    FMT   pcmFMT;  
    DATA   pcmDATA;  
 
    unsigned   short   m_pcmData;
    FILE   *fp,*fpCpy;  

    if (argc < 5)
    {
        show_usage();
        return -1;
    }
    sscanf(argv[1], "%s", src_file);
    sscanf(argv[2], "%s", dst_file);
    sscanf(argv[3], "%d", &channels);
    sscanf(argv[4], "%d", &sample_rate);
    if (argc>6)
    {
        sscanf(argv[5], "%d", &bits);
    }

    printf("parameter analyse succeess\n"); 

    if((fp=fopen(src_file,   "rb"))   ==   NULL) //读取文件  
    {  
        printf("open pcm file %s error\n", argv[1]);
        return -1;  
    }

    if((fpCpy=fopen(dst_file,   "wb+"))   ==   NULL) //为转换建立一个新文件  
    {    
        printf("create wav file error\n");  
        return -1; 
    }        

    //以下是创建wav头的HEADER;但.dwsize未定，因为不知道Data的长度。  
    strcpy(pcmHEADER.fccID,"RIFF");                    
    strcpy(pcmHEADER.fccType,"WAVE");  
    fseek(fpCpy,sizeof(HEADER),1); //跳过HEADER的长度，以便下面继续写入wav文件的数据; 

    //以上是创建wav头的HEADER;  
    if(ferror(fpCpy))  
    {    
        printf("error\n");  
    }  
    //以下是创建wav头的FMT;  
    pcmFMT.dwSamplesPerSec=sample_rate;  
    pcmFMT.dwAvgBytesPerSec=pcmFMT.dwSamplesPerSec*sizeof(m_pcmData);  
    pcmFMT.uiBitsPerSample=bits;  

    strcpy(pcmFMT.fccID,"fmt   ");  
    pcmFMT.dwSize=16;  
    pcmFMT.wBlockAlign=2;  
    pcmFMT.wChannels=channels;  
    pcmFMT.wFormatTag=1;  
    //以上是创建wav头的FMT;    

    fwrite(&pcmFMT,sizeof(FMT),1,fpCpy); //将FMT写入.wav文件;  
    //以下是创建wav头的DATA;   但由于DATA.dwsize未知所以不能写入.wav文件  
    strcpy(pcmDATA.fccID,"data");  

    pcmDATA.dwSize=0; //给pcmDATA.dwsize   0以便于下面给它赋值  
    fseek(fpCpy,sizeof(DATA),1); //跳过DATA的长度，以便以后再写入wav头的DATA;  
    fread(&m_pcmData,sizeof(unsigned   short),1,fp); //从.pcm中读入数据  

    while(!feof(fp)) //在.pcm文件结束前将他的数据转化并赋给.wav;  
    {  
        pcmDATA.dwSize+=2; //计算数据的长度；每读入一个数据，长度就加一；  
        fwrite(&m_pcmData,sizeof(unsigned   short),1,fpCpy); //将数据写入.wav文件;  
        fread(&m_pcmData,sizeof(unsigned   short),1,fp); //从.pcm中读入数据  
    }  

    fclose(fp); //关闭文件  
    pcmHEADER.dwSize=44+pcmDATA.dwSize;   //根据pcmDATA.dwsize得出pcmHEADER.dwsize的值  

    rewind(fpCpy); //将fpCpy变为.wav的头，以便于写入HEADER和DATA;  
    fwrite(&pcmHEADER,sizeof(HEADER),1,fpCpy); //写入HEADER  
    fseek(fpCpy,sizeof(FMT),1); //跳过FMT,因为FMT已经写入  
    fwrite(&pcmDATA,sizeof(DATA),1,fpCpy);   //写入DATA;  

    fclose(fpCpy);   //关闭文件  

    return 0;
}

