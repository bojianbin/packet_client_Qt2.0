
#include"bo.h"
#include"ffmtool.h"
AVCodec* codec;
AVCodecContext *c[6];
AVFrame *frame;
AVFrame *frameout;
AVPacket pack;

AVPicture pict;
struct SwsContext *sws;

const int i_to_speed[6] = {1800000,1000000,500000,100000,50000,30000};

int av_open_codec(){

    int i = 0;
    codec = avcodec_find_decoder(AV_CODEC_ID_H264);
    if(!codec){
        printf("unable to find encoder\n");
        exit(1);
    }
    for(i =0;i<6;i++){

        c[i] = avcodec_alloc_context3(codec);
        c[i]->bit_rate = i_to_speed[i];
        c[i]->width = 640;
        c[i]->height = 480;
        c[i]->time_base = (AVRational){1,10};
        c[i]->gop_size = 5;
        c[i]->max_b_frames = 0;
        c[i]->pix_fmt = AV_PIX_FMT_YUV420P;
        //AV_PIX_FMT_RGB24
        //pix_fmt_rgb24
        av_opt_set(c[i]->priv_data,"present","ultrafast",0);

    }//for(i = 0;i<6;i++)

    frame = avcodec_alloc_frame();
    frameout = avcodec_alloc_frame();
    av_image_alloc(frameout->data,frameout->linesize,640,480,PIX_FMT_RGB24,32);
    sws = sws_getContext(
                c[0]->width,
            c[0]->height,
            c[0]->pix_fmt,
            c[0]->width,
            c[0]->height,
            PIX_FMT_RGB24,
            SWS_BILINEAR,
            NULL,
            NULL,
            NULL);

}

int to_image(char * buf,int size,struct codec_need * needs,uint8_t ** data_,int *size_)
{




    int sp= 0;
    switch (needs->bit_rate) {
    case 1800000: sp = 0 ; break;
    case 1000000: sp = 1 ; break;
    case  500000: sp = 2 ; break;
    case  100000: sp = 3 ; break;
    case   50000: sp = 4 ; break;
    case   30000: sp = 5 ; break;
    default:
    {
        err_print("can not find bit_rate\n");
        exit(-1);
        break;
    }
    }//switch

    if (avcodec_open2(c[sp],codec,NULL) < 0){
        printf("av_open2 error \n");
        exit(-1);
    }



    av_init_packet(&pack);
    int framefinished;
    pack.data = (uint8_t *)buf;
    pack.size = size;

    //  printf("decodec--c[sp]--c[%d]\n",sp);
    if(avcodec_decode_video2(c[sp],frame,&framefinished,&pack)<0)
        printf("decode error\n");
    //av_free_packet(&pack);

    if(framefinished)
    {
        sws_scale(
                    sws,
                    (uint8_t const * const *)frame->data,
                    frame->linesize,
                    0,
                    c[sp]->height,
                    frameout->data,
                    frameout->linesize);



        //*data_ = (uint8_t *)malloc(c[sp]->height * frameout->linesize[0]);
        *size_ = c[sp]->height * frameout->linesize[0];

        bzero(*data_,*size_);
        memcpy(*data_,frameout->data[0],*size_);
        //SaveFrame(*data_,640,480);

        /////

        //////

    }//if framefinished


}

void codec_close(int bit_rate){//关闭不用的AVCodecContext *
    int sp;
    if(bit_rate <=0) return;
    switch (bit_rate) {
    case 1800000: sp = 0 ; break;
    case 1000000: sp = 1 ; break;
    case  500000: sp = 2 ; break;
    case  100000: sp = 3 ; break;
    case   50000: sp = 4 ; break;
    case   30000: sp = 5 ; break;
    default:
    {
        err_print("can not find bit_rate2\n");
        break;
    }
    }//switch

    av_frame_free(&frame);
    av_free(frame);
    av_frame_free(&frameout);
    av_free(frameout);
    avcodec_flush_buffers(c[sp]);
    //avcodec_close(c[sp]);
    for(size_t i = 0;i<6;i++){
        avcodec_close(c[i]);
        av_free(c[i]);
    }
    sws_freeContext(sws);

}
void  SaveFrame(u_char *p,int width, int height) {
  FILE *pFile;
  const char *szFilename ;
  int  y;

  // Open file
  szFilename = "/home/bo/tuxiang";
  pFile=fopen(szFilename, "wb");
  if(pFile==NULL)
    return;

  // Write header
  fprintf(pFile, "P6\n%d %d\n255\n", width, height);

  // Write pixel data
    fwrite(p, 1, width*height*3, pFile);

  // Close file
  fclose(pFile);
}
