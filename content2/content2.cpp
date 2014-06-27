#include "content2.h"
#include<QtWidgets>
#include"../show/widget.h"

content2::content2(QString ip,QString port,int pp, QWidget *parent)
    : QWidget(parent),ip_(ip),port_(port)
{
    QPalette palette;
    palette.setBrush(QPalette::Window,QBrush(QColor(250,255,240,150)));
    setPalette(palette);
    setAutoFillBackground(true);
    button = new QPushButton(this);
    button->setText("开始录制");
    button->setCheckable(true);
    connect(button,SIGNAL(toggled(bool)),this,SLOT(button_text(bool)));

    button2 = new QPushButton(this);
    button2->setText("屏幕截图");


    picture = new pic_show(this,ip,port);
    button->move( width()-10-button->width(),10 );
    connect(picture,SIGNAL(showmessage(QString)),this,SIGNAL(showmess(QString)));
    connect(button2,SIGNAL(clicked()),picture,SLOT(capture()));
}

content2::~content2()
{

    
}

void content2::resizeEvent(QResizeEvent *){


    picture->resize( height() *640 /480,height());
    picture->move( width()/2 - picture->width()/2,0 );
    button->move( width()-10-button->width(),10 );

    button2->move(button->x(),button->y()+button->height()+10);
}
pic_show * content2::pic_ptr(){
    return picture;
}
void content2::button_text(bool pp){

    if(pp == true){
        button->setText("停止录制");
        picture->startvideo();
        emit startvideo(ip_ + "/" + port_);
    }
    else{
        picture->endvideo();
        button->setText("开始录制");
        emit endvideo(ip_ + "/" + port_);
    }
}
