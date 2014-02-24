#include "widget.h"
#include"bo.h"
#include"mythread.h"
#include"content2/content2.h"
pic_show::pic_show( QWidget *parent,QString ip,QString port)
    : QWidget(parent)
{
    ip_ = ip;
    port_ = port;
    fullscreen = false;
    getvideo = false;
    QTimer *time1 = new QTimer(this);
    connect(time1,SIGNAL(timeout()),this,SLOT(pre_heart_beat()));
    time1->start(100);//100ms的定时

    QTimer *time2 = new QTimer(this);
    connect(time2,SIGNAL(timeout()),this,SLOT(check_run()));
    time2->start(30);

    image_buf = (uchar *)malloc(640*480*3);
    image_ = new QImage(image_buf,640,480,QImage::Format_RGB888);

    if(ip_ != "" && port_ != ""){

        thread1.setprot(ip_,port_);
        thread1.start();
    }

    connect(&thread1,SIGNAL(showmess(QString)),this,SIGNAL(showmessage(QString)));

    filedir = "PACKET_VIDEOSAVE";
}

pic_show::~pic_show()
{
    delete image_;
    free(image_buf);
    if(thread1.isRunning())
        thread1.stopp();

    thread1.wait();
    if(getvideo){//如果关闭时仍在录制,则释放
        endvideo();
    }
}
void pic_show::setprot(QString ip , QString port){

    ip_ = ip;
    port_ = port;
    thread1.setprot(ip,port);
    if(!thread1.isRunning()){
        thread1.start();
    }

}
void pic_show::pre_heart_beat(){

    if(!thread1.isRunning())
        return;
    thread1.heart_beat();
}

void pic_show::check_run(){

    if(!thread1.isRunning())
        return;

    thread1.ready_lock.lock();
    if(thread1.ready_to_go == true){
        to_image(thread1.ready,thread1.size);

        thread1.ready_to_go = false;
    }
    thread1.ready_lock.unlock();

}
void pic_show::to_image(uint8_t * buf, int size){

    //char ch[30];
    //sprintf(ch, "P6\n640 480\n255\n");
    if(getvideo == true){
        memcpy(videobuf,buf,size);
        invideo();
    }
    char *bb = (char *)malloc(size + 15);
    memcpy(bb,"P6\n640 480\n255\n",15);
    memcpy(bb+15,buf,size);

    if(image_->loadFromData((uchar *)bb,size+15,"PPM") == false)
        printf("image loaddata error\n");
    free(bb);
    update();
}
void pic_show::paintEvent(QPaintEvent *){

    QPixmap pixmap(640,480);
    pixmap = QPixmap::fromImage(*image_);
    pixmap = pixmap.scaled(size());
    QPainter paint(this);
    paint.drawPixmap(0,0,pixmap);


}

void pic_show:: SaveFrame(u_char *p,int width, int height) {
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

QSize pic_show::sizeHint() const{

    return QSize(640,480);
}
void pic_show::mouseDoubleClickEvent(QMouseEvent *){

    if(!fullscreen){

        setParent(0);
        showFullScreen();
        fullscreen = true;
    }
    else{

        fullscreen = false;
        setParent(parent_);
        show();
        QEvent *e = new QEvent(QEvent::Resize);
        qApp->notify(parent_,e);
        delete e;
    }

}
void pic_show::addparent(content2 * parent){

    parent_ = parent;
}
void pic_show::startvideo(){

    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);

    videobuf = (uint8_t *)malloc(640 * 480 *3);

    QDir dir(QDir::homePath());
    QDir dir2(QDir::homePath() + "/"+filedir);
    if(!dir2.exists())
       dir.mkdir(filedir);
    QString kk = QDate::currentDate().toString("yyyyMMdd") + "V"+QTime::currentTime().toString("hhmmss");
    absolutefilename = dir2.absolutePath() + "/" + ip_ + "V" + port_ + "V"+ kk +".mkv";
    char *name = (char *)malloc(100);
    bzero(name,100);
    strcat(name,dir2.absolutePath().toAscii().data());
    strcat(name,"/");
    strcat(name,ip_.toAscii().data());
    strcat(name,"V");
    strcat(name,port_.toAscii().data());
    strcat(name,"V");
    strcat(name,kk.toAscii().data());
    strcat(name,".mkv");

    file_ = name;

    avformat_alloc_output_context2(&oc,NULL,NULL,file_);
    if(!oc){
        emit showmessage("In getvideo could not deduce output format from filename");
        return;
    }
    fmt = oc->oformat;
    video_st  = NULL;
    if(fmt->video_codec != AV_CODEC_ID_NONE){//add stream
        video_codec =  avcodec_find_encoder(fmt->video_codec);
        if(!video_codec){
            emit showmessage("can not find encoder");
        }
        video_st = avformat_new_stream(oc,video_codec);
        if(!video_st)
            emit showmessage("can not alloc stream");
        video_st->id = oc->nb_streams - 1;
        AVCodecContext *c;
        c = video_st->codec;
        {
            c->codec_id = fmt->video_codec;
            c->bit_rate = thread1.bit_rate_;
            c->width = thread1.width_;
            c->height = thread1.height_;
            c->time_base.den = thread1.fps_;
            c->time_base.num = 1;
            c->gop_size = thread1.gopsize_;
            c->pix_fmt = AV_PIX_FMT_YUV420P;
        }
        if(oc->oformat->flags & AVFMT_GLOBALHEADER)
            c->flags |= CODEC_FLAG_GLOBAL_HEADER;

    }//add stream
    AVCodecContext *c = video_st->codec;
    int ret = avcodec_open2(c,video_codec,NULL);
    if(ret <0){
        emit showmessage("can not open video codec");
        return;
    }
    if(!(fmt->flags & AVFMT_NOFILE)){//open file if needed
        int ret = avio_open(&oc->pb,file_,AVIO_FLAG_WRITE);
        if(ret <0){
            emit showmessage("can not open file");
            return;
        }
    }
    ret = avformat_write_header(oc,NULL);
    if(ret < 0 ){
        emit showmessage("error when write header");
        return;
    }





    getvideo = true;
    tosave = avcodec_alloc_frame();
    sws = sws_getContext(
                640,
                480,
                PIX_FMT_RGB24,
                640,
                480,
                AV_PIX_FMT_YUV420P,
                SWS_BILINEAR,
                NULL,
                NULL,
                NULL);
    pts_ = 0;
    toencode = avcodec_alloc_frame();
    av_image_alloc(toencode->data,toencode->linesize,640,480,AV_PIX_FMT_YUV420P,32);

}

void pic_show::invideo(){

    avpicture_fill((AVPicture *)tosave,videobuf,PIX_FMT_RGB24,640,480);
    sws_scale(
                sws,
                (uint8_t const * const *)tosave->data,
                tosave->linesize,
                0,
                480,
                toencode->data,
                toencode->linesize);


    {//write frame
        AVPacket pack;
        int gotout;
        int ret;
        av_init_packet(&pack);
        pack.data = NULL;
        pack.size = 0;
        toencode->pts = pts_;
        ret = avcodec_encode_video2(video_st->codec,&pack,toencode,&gotout);
        if(ret< 0){
            emit showmessage("error while encoding video stream");
        }
        if(gotout){
            if(video_st->codec->coded_frame->key_frame)
                pack.flags |= AV_PKT_FLAG_KEY;
            pack.stream_index = video_st->index;
            av_interleaved_write_frame(oc,&pack);
            av_free_packet(&pack);
        }

    }
    pts_ += av_rescale_q(1,video_st->codec->time_base,video_st->time_base);


}
void pic_show::endvideo(){

    getvideo = false;

    //get delayed frames
        AVPacket pack;
        av_init_packet(&pack);
        pack.data = NULL;
        pack.size = 0;
        int gotout = 1;
        while(gotout){
            avcodec_encode_video2(video_st->codec,&pack,NULL,&gotout);
            if(gotout){
                if(video_st->codec->coded_frame->key_frame)
                    pack.flags |= AV_PKT_FLAG_KEY;
                pack.stream_index = video_st->index;
                av_interleaved_write_frame(oc,&pack);
                av_free_packet(&pack);
            }

        }

    av_write_trailer(oc);
    avcodec_close(video_st->codec);
    if(!(fmt->flags & AVFMT_NOFILE)){
        avio_close(oc->pb);
    }

    avformat_free_context(oc);
    free(videobuf);
    av_free(tosave);
    sws_freeContext(sws);
    av_frame_free(&toencode);
    av_free(toencode);
    free(file_);
}
