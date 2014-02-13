#include "contentwidget.h"
#include <QPalette>
#include"first_item_pre.h"
contentWidget::contentWidget(QWidget *parent) :
    QWidget(parent)
{
    QPalette palette;
    palette.setBrush(QPalette::Window,QBrush(QColor(250,255,240,150)));
    setPalette(palette);
    setAutoFillBackground(true);
    //mainlayout = new QVBoxLayout(this);

    add = new QAction("Add",this);
    connect(add,SIGNAL(triggered()),this,SLOT(additem()));
    addAction(add);
    setContextMenuPolicy(Qt::ActionsContextMenu);

}
void contentWidget::additem(){

    item_pre *pre = new item_pre;
    QString ip;
    QString port;
    if(pre->exec() == QDialog::Accepted){
        ip = pre->edit1->text();
        port = pre->edit2->text();
        delete pre;
        Widget *item = new Widget;
        item->changelabel(ip,port);
        connect(item,SIGNAL(close()),this,SLOT(close_item()));
        connect(item,SIGNAL(startconnect(QString,QString,int)),this,SIGNAL(startconnect(QString,QString,int)));
        connect(item,SIGNAL(findconnect(QString,QString,int)),this,SIGNAL(findconnect(QString,QString,int)));
        connect(item,SIGNAL(stopconnect(QString,QString,int)),this,SIGNAL(closeconnect(QString,QString,int)));
        connect(item,SIGNAL(closeconnect(QString,QString,int)),this,SIGNAL(closeconnect(QString,QString,int)));
        //item->setAttribute(Qt::WA_DeleteOnClose);
        actionlist.append(item);
        addactons();
    }
}
void contentWidget::addactons(){

    mainlayout  = qobject_cast<QVBoxLayout *>(layout());
    delete mainlayout;
    mainlayout = new QVBoxLayout;
    QList<Widget *>::const_iterator it = actionlist.begin();
    while(it != actionlist.end()){
        mainlayout->addWidget(*it);
        it++;
    }
    mainlayout->addStretch();
    mainlayout->setSpacing(0);
    mainlayout->setContentsMargins(0,0,0,0);
    setLayout(mainlayout);
}

void contentWidget::close_item(){

    Widget * item = qobject_cast<Widget *>(sender());
    QList<Widget *>::iterator pt = actionlist.begin();
    while(pt != actionlist.end()){
        if( *pt == item ){
            actionlist.erase(pt);
            delete(item);
        }
        pt++;
    }
}
