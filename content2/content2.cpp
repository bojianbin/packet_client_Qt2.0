#include "content2.h"
#include<QtGui>
#include"../show/widget.h"

content2::content2(QString ip,QString port,int pp, QWidget *parent)
    : QWidget(parent)
{
    QPalette palette;
    palette.setBrush(QPalette::Window,QBrush(QColor(250,255,240,150)));
    setPalette(palette);
    setAutoFillBackground(true);

    picture = new pic_show(this,ip,port);

}

content2::~content2()
{
    
}

void content2::resizeEvent(QResizeEvent *){


    picture->resize( height() *640 /480,height());
    picture->move( width()/2 - picture->width()/2,0 );

}
pic_show * content2::pic_ptr(){
    return picture;
}
