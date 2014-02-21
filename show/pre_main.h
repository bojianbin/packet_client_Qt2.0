#ifndef PRE_MAIN_H
#define PRE_MAIN_H
#include"bo.h"
void err_print(const char *);
void err_quit(const char *);
int max(int,int);

struct codec_need{

    int width;
    int height;
    int fps;//帧率
    int gopsize;
    int max_b_frames;
    uint32_t bit_rate;
};


struct buf_chip{
    uint32_t time;//帧序号
    int time2;//帧内序号
    char *buf;
    int size;
    struct buf_chip *next;

};
struct chip_queue{
  struct buf_chip *head;
  struct buf_chip *tail;
  int size;
};

int start_connet(int,int);

void queue_init(struct chip_queue *);
int chip_push(struct chip_queue*,struct buf_chip);
int chip_pop (struct chip_queue*,struct buf_chip *);
int chip_top (struct chip_queue *,struct buf_chip *);
uint32_t chip_top_time(struct chip_queue *);
char chip_empty(struct chip_queue *);
int chip_entity(struct chip_queue * );
void chip_destroy(struct chip_queue *);

int chips_to_buf(struct chip_queue *,char*buf,int *);
uint8_t protocol_handle(char *);


struct check_time{

    time_t old_time;
    int beats;
    int bit_rates;
};
int syn_time(struct codec_need *);
#endif // PRE_MAIN_H
