#ifndef CONTENT2_H
#define CONTENT2_H

#include <QWidget>
#include"../show/widget.h"

class content2 : public QWidget
{
    Q_OBJECT
    
public:
    content2(QString,QString,int, QWidget *parent = 0);
    ~content2();
    pic_show *pic_ptr();
public slots:
    //void show_pic(int);
    //void add_pic(QString,QString,int);
private:
    pic_show *picture;
protected:
    void resizeEvent(QResizeEvent *);
};

#endif // CONTENT2_H
