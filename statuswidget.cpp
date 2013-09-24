#include "statuswidget.h"
#include <QLabel>
#include <QHBoxLayout>

statusWidget::statusWidget(QWidget *parent) :
    QWidget(parent)
{
    QLabel *labelVersion=new QLabel(tr("zhuchengxu"));
    QLabel *labelHorse=new QLabel();
    QLabel *labelUpdate=new QLabel();
    QLabel *labelConn360=new QLabel();

    QHBoxLayout *mainLayout=new QHBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->addWidget(labelVersion);
    labelVersion->setContentsMargins(5,0,0,0);
    mainLayout->addWidget(labelHorse);
    mainLayout->addWidget(labelUpdate);
    mainLayout->addStretch();
    mainLayout->addWidget(labelConn360);
    labelConn360->setContentsMargins(0,0,40,0);
    setLayout(mainLayout);

    setFixedHeight(25);
}
