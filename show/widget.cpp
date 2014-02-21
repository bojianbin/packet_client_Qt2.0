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

}

pic_show::~pic_show()
{

    free(image_buf);
    if(thread1.isRunning())
       thread1.stopp();

    thread1.wait();
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
