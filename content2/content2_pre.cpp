#include"content2_pre.h"
#include "content2.h"
#include<QtGui>


content2_pre::content2_pre(QWidget *parent)
    : QWidget(parent)
{
    QPalette palette;
    palette.setBrush(QPalette::Window,QBrush(QColor(250,255,240,150)));
    setPalette(palette);
    setAutoFillBackground(true);

}

content2_pre::~content2_pre()
{

}

