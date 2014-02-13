#include "skinwidget.h"
#include <QSignalMapper>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPainter>

skinWidget::skinWidget(QString picName,QWidget *parent) :bkPicName(picName),
    QWidget(parent)
{
    QSignalMapper *signalMapper=new QSignalMapper(this);
    QStringList bkPicName;
    bkPicName<<":/icon/b1.jpg"<<":/icon/b2.jpg"<<":/icon/b3.jpg"<<":/icon/b4.jpg"<<":/icon/b5.jpg"<<":/icon/b6.jpg"<<":/icon/b7.jpg"<<":/icon/b8.jpg"<<":/icon/b9.jpg";
    QStringList tip;
    tip<<tr("1")<<tr("2")<<tr("3")<<tr("4")<<
             tr("5")<<tr("6")<<tr("7")<<tr("8")<<tr("9");

    QGridLayout *gridLayout=new QGridLayout;
    gridLayout->setSpacing(0);
    int r=0,c=0;
    for(int i=0;i<9;i++)
    {
        QPushButton *btn=new QPushButton;
        btn->setFlat(true);
        QIcon icon(bkPicName[i].left(bkPicName[i].indexOf("."))+"small.jpg");
        btn->setIcon(icon);
        btn->setIconSize(QSize(97,62));
        btn->setToolTip(tip[i]);
        connect(btn,SIGNAL(clicked()),signalMapper,SLOT(map()));
        signalMapper->setMapping(btn,bkPicName[i]);
        if(i%3==0)
        {
            r++;
            c=0;
        }
        gridLayout->addWidget(btn,r,c++);
    }
    connect(signalMapper,SIGNAL(mapped(QString)),this,SIGNAL(changeSkin(QString)));
    connect(signalMapper,SIGNAL(mapped(QString)),this,SLOT(setSkin(QString)));

    QVBoxLayout *mainLayout=new QVBoxLayout;
    mainLayout->addWidget(new QLabel(tr("genghuanpifu")),0,Qt::AlignHCenter);
    mainLayout->addLayout(gridLayout);
    setLayout(mainLayout);

   setWindowFlags(Qt::Popup);
}

void skinWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setBrush(QBrush(QPixmap(bkPicName)));
    painter.setRenderHints(QPainter::Antialiasing,true);
    painter.setPen(Qt::black);
    painter.drawRect(rect());
}
void skinWidget::setSkin(QString picName)
{
    bkPicName=picName;
    update();
}
