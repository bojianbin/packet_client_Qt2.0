#include "titlewidget.h"
#include "sysbutton.h"
#include "mypushbutton.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QApplication>
#include <QMessageBox>
#include <QMouseEvent>
#include<cmath>

titleWidget::titleWidget(QWidget *parent) :
    QWidget(parent)
{
    QLabel *versionText=new QLabel(tr("2013-06-16"));

    btnSkin=new myPushButton("SkinButton.png",tr("huanfu"));
    connect(btnSkin,SIGNAL(clicked()),this,SIGNAL(showSkin()));
    btnMenuBar=new sysButton("title_bar_menu.png",tr("zhucaidan"));
    btnMin=new sysButton("sys_button_min.png",tr("zuixiao"));
    connect(btnMin,SIGNAL(clicked()),this,SIGNAL(showMin()));
    btnMax=new sysButton("sys_button_max.png",tr("zuida"));
    connect(btnMax,SIGNAL(clicked()),this,SIGNAL(showMax()));
    btnClose=new sysButton("sys_button_close.png",tr("guanbi"));
    connect(btnClose,SIGNAL(clicked()),parentWidget(),SLOT(close()));

    QHBoxLayout *mainLayout=new QHBoxLayout;
    mainLayout->addWidget(versionText,0,Qt::AlignVCenter);
    versionText->setContentsMargins(5,0,0,0);
    mainLayout->addStretch();
    mainLayout->addWidget(btnSkin,0,Qt::AlignVCenter);
    btnSkin->setContentsMargins(0,0,5,0);
    mainLayout->addWidget(btnMenuBar);
    mainLayout->addWidget(btnMin);
    mainLayout->addWidget(btnMax);
    mainLayout->addWidget(btnClose);

    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0,0,0,0);
    setLayout(mainLayout);
    setFixedHeight(25);
    isMove=false;
}

void titleWidget::mousePressEvent(QMouseEvent *e)
{
    pressedPoint=e->globalPos();
    isMove=true;
    tmp = pressedPoint;


}
void titleWidget::mouseMoveEvent(QMouseEvent *e)
{
    if( (e->buttons()&Qt::LeftButton) && isMove)
    {

        QPoint nowParPoint;
        nowParPoint.setX(e->globalX()-pressedPoint.x());
        nowParPoint.setY(e->globalY()-pressedPoint.y());
      //  if(abs( nowParPoint.x() )  > 5 || abs(nowParPoint.y())> 5 )
           {
        emit move( nowParPoint);}

    }
}
void titleWidget::mouseReleaseEvent(QMouseEvent *)
{
    if(isMove)
        isMove=false;
    emit move(QPoint(10000,10000));
}
void titleWidget::mouseDoubleClickEvent(QMouseEvent *e)
{
    if(e->x()+170>=this->width())
        return;
    emit showMax();
}
