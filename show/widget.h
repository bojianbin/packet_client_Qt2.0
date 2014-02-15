#ifndef SHOWWIDGET_H
#define SHOWWIDGET_H

#include <QWidget>
#include<QtGui>
#include"mythread.h"
#include"bo.h"
class content2;
class pic_show : public QWidget
{
    Q_OBJECT
    
public:
    QSize sizeHint() const;
    pic_show(QWidget *parent = 0,QString = "",QString = "" );
   // pic_show(QWidget * = 0);
    ~pic_show();
    void addparent(content2 *);
public slots:
    void setprot(QString ,QString);
    void check_run();
    void pre_heart_beat();

private slots:
protected:
    void paintEvent(QPaintEvent *);
    void mouseDoubleClickEvent(QMouseEvent *);
private:
    content2 * parent_;
    bool fullscreen;
    mythread thread1;
    QString ip_;
    QString port_;
    QImage *image_;
    uchar *image_buf;
    void to_image(uint8_t *,int);
    void SaveFrame(u_char *,int , int );
};

#endif // WIDGET_H
