#ifndef FFMTOOL_H
#define FFMTOOL_H
#include"bo.h"
#include"pre_main.h"
int av_open_codec();
int to_image(char *,int,struct codec_need *,uint8_t **,int * );
//void show();
//int sdl_pre();


void codec_close(int );

void  SaveFrame(u_char *,int, int );





#endif // FFMTOOL_H
