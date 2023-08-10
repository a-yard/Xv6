#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    char p_c;
    char pipe_data[1640];
    int n = 0;
    char sh_data[64];
    strcpy(sh_data, argv[2]);
    while (read(0, &p_c, sizeof(p_c)))
    {
        if(p_c!='\n' ){//&& p_c!='"'
            pipe_data[n] = p_c;
            n++;
        }
        //printf("%c\n",p_c);
        if (p_c=='\n' )//|| p_c=='\\' 
        {
            // if(p_c=='\\'){
            //     read(0, &p_c, sizeof(p_c));
            // }
            pipe_data[n]='\0';
            int pid;
            char *cs[] = {argv[0], sh_data, pipe_data, 0};
            pid = fork();
            if (pid == 0)
            {
                exec(argv[1], cs);
            }
            else
            {
                int status;
                wait(&status);
            }
            pipe_data[0]='\0';
            n=0;
        }

    }
    close(0);

    exit(0);
}