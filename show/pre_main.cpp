
#include"pre_main.h"

int start_connet(int fd, int speed){
    char *buf;
    int n;
    buf = (char *)malloc(29*sizeof(char));
    bzero(buf,29);
    *(int *)(buf + 25) = htonl(speed);

    if( (n = sendto(fd,buf,29,0,NULL,0) )<= 0){
        err_print("start_connect error\n");
        free(buf);
        return -1;
    }
    free(buf);
    return 0;

}

void err_print(const char* ch)
{
    size_t n;
    n = strlen(ch);
    write(STDERR_FILENO,ch,n);
}
void err_quit(const char * ch)
{
    size_t n;
    n = strlen(ch);
    write(STDERR_FILENO,ch,n);
    exit(-1);
}
int max(int a, int b){
    if( a > b )
        return a;
    else
        return b;
}

void queue_init(struct chip_queue *queue ){
    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;
}
int chip_push(struct chip_queue * que, struct buf_chip chip){
    struct buf_chip *tmp = (struct buf_chip *)malloc(sizeof(struct buf_chip));
    *tmp = chip;
    tmp->next = NULL;
    if(que->head){
        struct buf_chip *a ;
        struct buf_chip *pre;
        for(a = que->head,pre = NULL ; a &&(a->time2 > tmp->time2) ; a = a->next){
            pre = a;
        }
        if(a != NULL && a->time2 == tmp->time2){
            return -1;
        }
        if(pre != NULL){
           tmp->next = pre->next;
           pre->next = tmp;
        }
        else{
            tmp->next =  que->head;
            que->head = tmp;
        }
        if(a == NULL)
            que->tail = tmp;
    }else{
        que->head = tmp;
        que->tail = tmp;
    }
    que->size++;
return 0;
}
int chip_pop(struct chip_queue * que, struct buf_chip * chip){

    struct buf_chip *tmp;
    tmp = que->head;
    if(tmp){
        if(! tmp->next)
            que->tail = NULL;
        que->head = tmp->next;
        *chip = *tmp;
       free(tmp);
        que->size--;
        return 0;
    }

    return -1;
}

int chip_top(struct chip_queue *que, struct buf_chip *chip){

    if(que->head){
        *chip = *(que->head);
        return 0;
    }
    return -1;
}
uint32_t chip_top_time(struct chip_queue * que){

     return que->head->time;
}
char chip_empty(struct chip_queue *que){

    if(que->head)
        return 0;
    return 1;
}
int chip_entity(struct chip_queue * que){

    if( que->size && que->size == que->head->time2)
        return 0;//que中的报文是完整的
    else
        return -1;//不完整的报文
}

int chips_to_buf(struct chip_queue * que, char *buf,int *total){

    int n;int size = 0;
    int index = 0;
    struct buf_chip tmp;
    while( !chip_empty(que) ){
        chip_pop(que,&tmp);
        printf(" (%d %d )",tmp.time,tmp.time2);
        memcpy(buf+index,tmp.buf,tmp.size);
        size += tmp.size;
        index += tmp.size;
        free(tmp.buf);
    }
    printf("\n");
    *total = size;
    printf("the total size is %d\n",*total);
    return 0;

}
void chip_destroy(chip_queue * que){

    struct buf_chip tmp;
    while( !chip_empty(que) ){

        chip_pop(que,&tmp);
        free(tmp.buf);
    }
}
uint8_t protocol_handle(char * ch){

    uint8_t pp;
    pp = *ch & 0xc0;
    if(pp ==  0x40)
        return 1;//数据包

    pp = *ch & 0xf0;
    if(pp == 0x10)
        return 2;//服务器应答

}

struct check_time SYN;
//-1表示需要发送延迟报文
int syn_time(struct codec_need * needs){

    if(needs->bit_rate != SYN.bit_rates){
        SYN.bit_rates = needs->bit_rate;
        SYN.old_time = time(NULL);
        SYN.beats = 1;
        return 0;
    }
    if(time(NULL) - SYN.old_time < 10){
        SYN.beats++;
        return 0;
    }
    if(++SYN.beats <10*10*0.7){
        err_print("发送延迟报文\n");
        return -1;
    }
    SYN.old_time = time(NULL);
    SYN.beats = 1;
    return 0;

}
