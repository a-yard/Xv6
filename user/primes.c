#include "kernel/types.h"
#include "user/user.h"

void setprocess(int p[2]){
    int theone;
    close(p[1]);
    read(p[0],&theone,sizeof(theone));
    printf("prime %d\n",theone);
    int p_tmp[2];
    pipe(p_tmp);
    int tmp;
    int flag=0;
    while(read(p[0],&tmp,sizeof(tmp))){
        if(tmp%theone!=0){
            write(p_tmp[1],&tmp,sizeof(tmp));
            flag=1;
        }
    }
    close(p_tmp[1]);
    close(p[0]);
    if(flag==1){
        int pid;
        pid = fork();
        if(pid==0){
            setprocess(p_tmp);
        }else{
            int status;
            wait(&status);
        }
    }else{
        close(p_tmp[0]);
        close(p_tmp[1]);
    }
    exit(0);
}

int main(){
    int p[2];
    pipe(p);
    
    for(int i=2;i<=35;i++){
        write(p[1],&i,sizeof(int));
    }
    setprocess(p);
    
    exit(0);
}