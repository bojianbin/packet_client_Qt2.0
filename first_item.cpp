#include "first_item.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setFixedHeight(60);
    setSizePolicy( QSizePolicy::Expanding,QSizePolicy::Fixed);
    text = new QLabel(this);
    text->setText("NO other comments");
    settpalette(255);
    ip = "0";
    port = "0";
    label = QString("Adress:")+ip+QString("::")+port;


    dele = new QPushButton("delete",this);
    find = new QPushButton("find",this);
    box = new QComboBox(this);
    start = new QPushButton("start");
    stop = new QPushButton("stop");
    dele->setFixedSize(50,50);
    start->setFixedSize(50,50);
    find->setFixedSize(50,50);
    stop->setFixedSize(50,50);
    box->setFixedSize(60,50);
    box->addItem("UDP");
    box->addItem("TCP");

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addStretch();
    vbox->addWidget(text);
    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addLayout(vbox);
    hbox->addStretch();
    hbox->addWidget(box);
    hbox->addWidget(start);
    hbox->addWidget(stop);
    hbox->addWidget(find);
    hbox->addWidget(dele);

    setLayout(hbox);

   // setAttribute(Qt::WA_DeleteOnClose);
    connect(dele,SIGNAL(clicked()),this,SLOT(close()));
    //connect(dele,SIGNAL(clicked()),this,SLOT(stopenter()));
    connect(find,SIGNAL(clicked()),this,SLOT(findenter()));
    connect(start,SIGNAL(clicked()),this,SLOT(startenter()));
    connect(stop,SIGNAL(clicked()),this,SLOT(stopenter()));
    setAutoFillBackground(true);




}

Widget::~Widget()
{

}
void Widget::changetext(QString string){
    text->setText(string);
    return ;
}

void Widget::settpalette(int p){

    QPalette palette;
    QLinearGradient grd = QLinearGradient(0,0,0,60);
    grd.setColorAt(0,QColor(186,85,211,p));
    grd.setColorAt(0.5,QColor(128,0,128,p));
    grd.setColorAt(1,QColor(186,85,211,p));

    palette.setBrush(QPalette::Window,QBrush(grd));
    setPalette(palette);
}
void Widget::enterEvent(QEvent *e){
    settpalette(150);
}
void Widget::leaveEvent(QEvent *e){
    settpalette(255);
}
void Widget::paintEvent(QPaintEvent *e){

    QPainter paint(this);
    paint.setRenderHint(QPainter::Antialiasing);
    paint.setPen(Qt::red);
    paint.drawText(10,20,label);


}
void Widget::changelabel(QString ip_,QString port_){

    QPainter paint(this);
    paint.setRenderHint(QPainter::Antialiasing);
    paint.setPen(Qt::red);
    label = QString("Adress:")+ip_+QString("::")+port_;
    paint.drawText(10,10,label);
    ip = ip_;
    port = port_;
}
void Widget::stopenter(){
    emit stopconnect(ip,port,box->currentIndex());
}
void Widget::startenter(){

    emit startconnect(ip,port,box->currentIndex());
}
void Widget::findenter(){

    emit findconnect(ip,port,box->currentIndex());
}
void Widget::closeenter(){

    emit closeconnect(ip,port,box->currentIndex());
}
void Widget::closeEvent(QCloseEvent *e){

    stopenter();
    e->accept();
}
