#include "toolwidget.h"
#include "toolbutton.h"
#include <QLabel>
#include <QHBoxLayout>

toolWidget::toolWidget(QWidget *parent):
    QWidget(parent)
{
    toolButton *tbTiJian=new toolButton(":/icon/p.png",tr("设备列表"));
    toolButton *tbMuMa=new toolButton(":/icon/l.png",tr("监控界面"));
    toolButton *tbLouDong=new toolButton(":/icon/e.png",tr("信息浏览"));
    toolButton *tbXiTong=new toolButton(":/icon/h.png",tr("保存信息"));
    toolButton *tbQingLi=new toolButton(":/icon/a.png",tr("检索查询"));
    toolButton *tbJiaSu=new toolButton(":/icon/c.png",tr("6"));
    toolButton *tbMenZhen=new toolButton(":/icon/d.png",tr("7"));
    toolButton *tbRuanJian=new toolButton(":/icon/n.png",tr("8"));
    toolButton *tbGongNeng=new toolButton(":/icon/j.png",tr("9"));


    QLabel *logoLabel2 =new QLabel;
    QPixmap pixmap2(":/icon/penguin3.png");
    logoLabel2->setPixmap(pixmap2);
    logoLabel2->setFixedSize(pixmap2.size());
    logoLabel2->setCursor(Qt::PointingHandCursor);

    QHBoxLayout *mainLayout=new QHBoxLayout;
    mainLayout->setContentsMargins(5,0,5,0);
    mainLayout->addWidget(tbTiJian);
    mainLayout->addWidget(tbMuMa);
    mainLayout->addWidget(tbLouDong);
    mainLayout->addWidget(tbXiTong);
    mainLayout->addWidget(tbQingLi);
    mainLayout->addWidget(tbJiaSu);
    mainLayout->addWidget(tbMenZhen);
    mainLayout->addWidget(tbRuanJian);
    mainLayout->addWidget(tbGongNeng);
    mainLayout->addStretch();

    mainLayout->addWidget(logoLabel2,0,Qt::AlignBottom);
    setLayout(mainLayout);

    setFixedHeight(80);
}
