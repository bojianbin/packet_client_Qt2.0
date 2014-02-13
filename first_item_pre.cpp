#include"first_item_pre.h"

item_pre::item_pre(QWidget *parent):QDialog(parent){

    label1 = new QLabel("IP地址:",this);
    label2 = new QLabel("端口号:",this);
    edit1 = new QLineEdit(this);
    edit2 = new QLineEdit(this);
    button = new QPushButton("OK",this);
    QGridLayout *lay = new QGridLayout;
    lay->addWidget(label1,0,0);
    lay->addWidget(edit1,0,1);
    lay->addWidget(label2,1,0);
    lay->addWidget(edit2,1,1);
    lay->addWidget(button,2,1);
    setLayout(lay);
    connect(button,SIGNAL(clicked()),this,SLOT(accept()));

    QPalette palette;
    palette.setColor(QPalette::WindowText,Qt::black);
    setPalette(palette);

}
item_pre::~item_pre(){


}
