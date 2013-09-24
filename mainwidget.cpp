#include "mainwidget.h"
#include <QBitmap>
#include <QPainter>
#include <QBrush>
#include<QTimer>
#include<QtGui>

#include "titlewidget.h"
#include "toolwidget.h"
#include "statuswidget.h"
#include "contentwidget.h"
#include "skinwidget.h"

#include <QVBoxLayout>
#include <QApplication>
#include <QDesktopWidget>

mainWidget::mainWidget(QWidget *parent)
    : QWidget(parent)
{
    times = 1;
    resize(850,600);
    //setWindowFlags(Qt::FramelessWindowHint);
    bkPicName=":/icon/b2.jpg";

    titleWidget *titleW=new titleWidget;
    connect(titleW,SIGNAL(showMax()),this,SLOT(showMax()));
    connect(titleW,SIGNAL(showMin()),this,SLOT(showMin()));
    connect(titleW,SIGNAL(showSkin()),this,SLOT(showSkinWidget()));
    connect(titleW,SIGNAL(move(QPoint)),this,SLOT(get_move(QPoint)));

    toolWidget *toolW=new toolWidget;
    toolW->setFocus();
    contentWidget *contentW=new contentWidget;
    statusWidget *statusW=new statusWidget;

    QVBoxLayout *mainLayout=new QVBoxLayout;
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->addWidget(titleW);
    mainLayout->addWidget(toolW);
    mainLayout->addWidget(contentW);
    contentW->setContentsMargins(1,5,1,0);
    mainLayout->addWidget(statusW);

    setLayout(mainLayout);


}
void mainWidget::get_move(QPoint hehe)
{
    if(hehe.x() == 10000 && hehe.y() == 10000)
    {begin = pos();return;}
    move(begin +hehe);

}
mainWidget::~mainWidget()
{
    
}

void mainWidget::paintEvent(QPaintEvent *)
{ begin = pos();
    QBitmap bitmap(this->size());
    bitmap.fill(Qt::color0);
    QPainter painter(&bitmap);
    painter.setBrush(QBrush(Qt::color1));
    painter.drawRoundedRect(bitmap.rect(),5,5);
    setMask(bitmap);

    QPixmap pixmap(this->size());
    pixmap.fill();
    painter.end();
    painter.begin(&pixmap);
    painter.setRenderHints(QPainter::Antialiasing,true);
    QBrush brush;
    brush.setStyle(Qt::TexturePattern);
    brush.setTextureImage(QImage(bkPicName));
    painter.setBrush(brush);
    painter.setPen(Qt::black);
    painter.drawRoundedRect(rect(),5,5);
    painter.end();
    painter.begin(this);
    painter.drawPixmap(this->rect(),pixmap);
}
void mainWidget::showMin()
{
    showMinimized();
}
void mainWidget::showMax()
{
    static bool isMax=false;
    if(isMax)
    {
        move(normalTopLeft);
        resize(850,600);
        isMax=false;
    }
    else
    {
        normalTopLeft=this->pos();
        setGeometry(QApplication::desktop()->availableGeometry());
        isMax=true;
    }
}

void mainWidget::showSkinWidget()
{
    skinWidget *skinW=new skinWidget(bkPicName);
    skinW->setAttribute(Qt::WA_DeleteOnClose);
    connect(skinW,SIGNAL(changeSkin(QString)),this,SLOT(setPicName(QString)));
    QPoint p=rect().topRight();
    p.setX(p.x()-150-350);
    p.setY(p.y()+30);
    skinW->move(this->mapToGlobal(p));
    skinW->show();
}
void mainWidget::setPicName(QString picName)
{
    bkPicName=picName;
    update();
}
void mainWidget::closeEvent(QCloseEvent * e )
{
    if(times == 1)
    {

        time = new QTimer(this);
    connect(time,SIGNAL(timeout()),this,SLOT(time_get()));
    time->start(100);}

    if (times > 0 ) {e->ignore(); return ;}
    if(times<=0)  {time->stop(); e->accept();}


}
void mainWidget::time_get()
{
    times =times -  0.1;
   setWindowOpacity(times);

   if(times <= 0) close();


}
