
#include"bo.h"
#include"sock.h"

int send_delay(int fd){

    char ch;
    ch = '\0';
    ch = 0x20;
    if(sendto(fd,&ch,1,0,NULL,0) <0)
        printf("delay send error\n");

}
