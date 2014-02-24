#include "toolwidget.h"
#include "toolbutton.h"
#include <QLabel>
#include <QHBoxLayout>

toolWidget::toolWidget(QWidget *parent):
    QWidget(parent)
{
    index = -1;
    toolButton *t1=new toolButton(":/icon/p.png",tr("设备列表"));
    list.append(t1);
    t2=new toolButton(":/icon/l.png",tr("监控界面"));
    list.append(t2);
    toolButton *t3=new toolButton(":/icon/e.png",tr("信息浏览"));
    list.append(t3);
    toolButton *t4=new toolButton(":/icon/h.png",tr("录制信息"));
    list.append(t4);
    toolButton *t5=new toolButton(":/icon/a.png",tr("检索查询"));
    list.append(t5);

   /* toolButton *tbJiaSu=new toolButton(":/icon/c.png",tr("6"));
    toolButton *tbMenZhen=new toolButton(":/icon/d.png",tr("7"));
    toolButton *tbRuanJian=new toolButton(":/icon/n.png",tr("8"));
    toolButton *tbGongNeng=new toolButton(":/icon/j.png",tr("9"));
*/
    connect(t1,SIGNAL(myToolClicked()),this,SLOT(change_index1()));
    connect(t2,SIGNAL(myToolClicked()),this,SLOT(change_index2()));
    connect(t3,SIGNAL(myToolClicked()),this,SLOT(change_index3()));
    connect(t4,SIGNAL(myToolClicked()),this,SLOT(change_index4()));
    connect(t5,SIGNAL(myToolClicked()),this,SLOT(change_index5()));


    QLabel *logoLabel2 =new QLabel;
    QPixmap pixmap2(":/icon/penguin3.png");
    logoLabel2->setPixmap(pixmap2);
    logoLabel2->setFixedSize(pixmap2.size());
    logoLabel2->setCursor(Qt::PointingHandCursor);

    QHBoxLayout *mainLayout=new QHBoxLayout;
    mainLayout->setContentsMargins(5,0,5,0);
    mainLayout->addWidget(t1);
    mainLayout->addWidget(t2);
    mainLayout->addWidget(t3);
    mainLayout->addWidget(t4);
    mainLayout->addWidget(t5);
    /*mainLayout->addWidget(tbJiaSu);
    mainLayout->addWidget(tbMenZhen);
    mainLayout->addWidget(tbRuanJian);
    mainLayout->addWidget(tbGongNeng);*/
    mainLayout->addStretch();

    mainLayout->addWidget(logoLabel2,0,Qt::AlignBottom);
    setLayout(mainLayout);

    setFixedHeight(80);
}
void toolWidget::change_index1(){

    if(1 == index)
        return;
    if(index != -1)
        list[index - 1]->first_bk();
    index = 1;
    emit click_tool(index-1);
}

void toolWidget::change_index2(){

    if(2 == index)
        return;
    if(index != -1)
        list[index - 1]->first_bk();
    index = 2;
    emit click_tool(index-1);
}
void toolWidget::change_index3(){

    if(3 == index)
        return;
    if(index != -1)
        list[index - 1]->first_bk();
    index = 3;
    emit click_tool(index-1);
}
void toolWidget::change_index4(){

    if(4 == index)
        return;
    if(index != -1)
        list[index - 1]->first_bk();
    index = 4;
    emit click_tool(index-1);
}
void toolWidget::change_index5(){

    if(5 == index)
        return;
    if(index != -1)
        list[index - 1]->first_bk();
    index = 5;
    emit click_tool(index-1);
}
