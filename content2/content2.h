#ifndef CONTENT2_H
#define CONTENT2_H

#include <QWidget>
#include"../show/widget.h"
class QPushButton;
class content2 : public QWidget
{
    Q_OBJECT
signals:
    void showmess(QString);
    void startvideo(QString);
    void endvideo(QString);
public:
    content2(QString,QString,int, QWidget *parent = 0);
    ~content2();
    pic_show *pic_ptr();
public slots:
    //void show_pic(int);
    //void add_pic(QString,QString,int);
private:
    QString ip_;
    QString port_;
    QPushButton * button;
    pic_show *picture;
private slots:
    void button_text(bool);
protected:
    void resizeEvent(QResizeEvent *);
};

#endif // CONTENT2_H
