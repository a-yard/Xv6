#include "kernel/types.h"
#include "user/user.h"

int main(){
    char buf='a';
    int p1[2];
    pipe(p1);
    int p2[2];
    pipe(p2);
    int pid = fork();
    
    if(pid==0){
        int cpid;
        cpid = getpid();
        close(p1[1]);
        char p1cdata[2];
        read(p1[0],p1cdata,sizeof(p1cdata));
        printf("%d: received ping\n",cpid);
        close(p2[0]);
        write(p2[1],&buf,sizeof(char));

    }else{
        int ppid;
        ppid = getpid();
        char p1data[2];
        close(p1[0]);
        write(p1[1],&buf,sizeof(char));
        close(p2[1]);
        read(p2[0],p1data,sizeof(p1data));
        printf("%d: received pong\n",ppid);
    }
    exit(0);
}