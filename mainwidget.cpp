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
#include"content2/content2.h"
#include"content2/content2_pre.h"
#include<QMap>
#include<QEvent>
#include"toolbutton.h"
/*
 *contentWidget 是第一个
 *content2_pre 是第二个（未有连接时的情况）
 *content2 是第二个（有连接的情况），有几个不同的连接就有几个content2
 **/
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

    toolW=new toolWidget;
    toolW->setFocus();
    contentWidget *contentW=new contentWidget;

    connect(contentW,SIGNAL(startconnect(QString,QString,int)),this,SLOT(startconnet(QString,QString,int)));
    connect(contentW,SIGNAL(findconnect(QString,QString,int)),this,SLOT(findconnet(QString,QString,int)));
    connect(contentW,SIGNAL(closeconnect(QString,QString,int)),this,SLOT(closeconnect(QString,QString,int)));

    statusWidget *statusW=new statusWidget;
    QVBoxLayout *mainLayout=new QVBoxLayout;
    con_pre = new content2_pre;

    browser = new QTextBrowser;
    browser->setStyleSheet("QTextBrowser{background-color:black}");
    browser->setTextColor(Qt::white);



    stacked = new QStackedLayout;
    stacked->addWidget(contentW);
    stacked->addWidget(con_pre);
    stacked->addWidget(browser);
    stacked->setCurrentIndex(0);
    connect(toolW,SIGNAL(click_tool(int)),stacked,SLOT(setCurrentIndex(int )));

    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->addWidget(titleW);
    mainLayout->addWidget(toolW);
    mainLayout->addLayout(stacked);
    contentW->setContentsMargins(1,5,1,0);
    mainLayout->addWidget(statusW);

    setLayout(mainLayout);
    event = new QEvent(QEvent::MouseButtonRelease);

}
void mainWidget::get_move(QPoint hehe)
{
    if(hehe.x() == 10000 && hehe.y() == 10000)
    {
        begin = pos();
        //move(begin);
        return;
    }
    move(begin +hehe);

}
mainWidget::~mainWidget()
{
    delete event;
}

void mainWidget::paintEvent(QPaintEvent *)
{
    begin = pos();
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

   if(times <= 0)
       close();


}
void mainWidget::findconnet(QString ip_, QString port_, int qq_){

    QString tmp;
    tmp = ip_ + port_;
    if(pic_list.contains(tmp)){
        stacked->removeWidget(stacked->widget(1));
        stacked->insertWidget(1,pic_list.value(tmp) );
        toolW->t2->setpressed_true();
        qApp->notify((QObject *)(toolW->t2),event);
    }
}
void mainWidget::startconnet(QString ip_, QString port_, int qq_){

    QString tmp ;
    tmp = ip_ + port_;
    if(pic_list.contains(tmp)){
        pic_num[tmp] += 1;
        stacked->removeWidget(stacked->widget(1));
        stacked->insertWidget(1,pic_list.value(tmp) );
        toolW->t2->setpressed_true();
        qApp->notify((QObject *)(toolW->t2),event);

    }else{
        content2 * con2 = new content2(ip_,port_,qq_);
        connect(con2,SIGNAL(showmess(QString)),this,SLOT(showmess(QString)));
        con2->pic_ptr()->addparent(con2);
        pic_list.insert(tmp,con2);
        pic_num.insert(tmp,1);

        stacked->removeWidget(stacked->widget(1));
        stacked->insertWidget(1,con2 );
        toolW->t2->setpressed_true();
        qApp->notify((QObject *)(toolW->t2),event);

    }
}
void mainWidget::closeconnect(QString ip_, QString port_, int qq_){

    QString tmp ;
    tmp = ip_ + port_;
    if(pic_list.contains(tmp)){

        if(pic_num.value(tmp)== 1){//仅剩这一个连接


            if(pic_list.value(tmp) == stacked->widget(1)){

                stacked->removeWidget(stacked->widget(1));
                stacked->insertWidget(1,con_pre );
            }
            showmess( ip_ + "::"+port_ +"  " + "closed");
            delete pic_list.value(tmp);
            pic_num.remove(tmp);
            pic_list.remove(tmp);


        }
        pic_num[tmp]--;
    }

}

void mainWidget::showmess(QString str){

    QString time;
    time = QTime::currentTime().toString();
    QString show = time + "; "+str;

    browser->append(show);
}







