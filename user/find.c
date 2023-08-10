#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

char* fntname(char * str){
   static char  buf[64];
    int len = strlen(str);
    int n=0;
    for(int i=len-1;i>=0;i--){
        if(str[i]!='/')n++;
        else break;
    }
    int flag=0;
    for(int i = len-n;i<len;i++){
        buf[flag] = str[i];
        flag++;
    }
    buf[flag]='\0';
    return buf;
}

void find(char * path,char * obj){
    
    char buf[64],*p;
    p = buf + strlen(buf);
    struct dirent dn;
    struct stat st;
    int fd;
    fd = open(path,0);
    if(fd<0){
        printf("cannot open %s\n",path);
    }
    fstat(fd,&st);
    switch (st.type)
    {
    case T_DIR:
        while(read(fd,&dn,sizeof(dn))==sizeof(dn)){
            strcpy(buf,path);
            if(dn.inum!=0){
                if(strcmp(dn.name,".")!=0 && strcmp(dn.name,"..")!=0){
                    p = buf + strlen(buf);
                    if(strlen(buf)!=0){
                        *p++ = '/';
                    }
                    memmove(p,dn.name,DIRSIZ);
                    //printf("%s\n",buf);
                    find(buf,obj);
                }
            }
        }
        break;
    case T_FILE:
        //printf("%s\n",fntname(path));
        if(strcmp(fntname(path),obj)==0){
            printf("%s\n",path);
        }
        close(fd);
        break;
    case T_DEVICE:

        break;
    default:
        printf("err the default\n");
        printf("open : %d\n",fd);
        break;
    }
}

int main(int argc, char *argv[]){
    if(argc!=3){
        printf("the err\n");
        exit(1);
    }
    find(argv[1],argv[2]);
    exit(0);
}