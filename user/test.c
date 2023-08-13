#include "kernel/types.h"
#include "user.h"

int main(){
    uint64 tmp = 0x100;
    tmp = (uint64)tmp>>1;
    printf("%p\n",tmp);
    exit(0);
}