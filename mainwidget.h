#ifndef MAINWIDGET_H
#define MAINWIDGET_H
//#include<QtGui>
#include <QtGui/QWidget>
#include<QMap>
#include<QEvent>
#include<QTextBrowser>
class content2;
class content2_pre;
class QStackedLayout;
class toolWidget;

class mainWidget : public QWidget
{
    Q_OBJECT
    
public:
    mainWidget(QWidget *parent = 0);
    ~mainWidget();

protected:
    void closeEvent(QCloseEvent *);
    void paintEvent(QPaintEvent *);
private:

    QEvent *event;
    toolWidget *toolW;
    QTimer *time;
    double times;
    QPoint begin;
    QString bkPicName;
    QPoint normalTopLeft;

    QTextBrowser *browser;
    QTextBrowser *video_browser;
    content2_pre *con_pre;
    QStackedLayout *stacked;
   // QList<content2 *>list;

    QMap<QString,content2*> pic_list;
    QMap<QString,int>pic_num;

    //录制
    QList<QString>video_list;//正在录制中

private slots:

    //录制
    void recv_startvideo(QString);
    void recv_endvideo(QString);


    void findconnet(QString ,QString,int);
    void startconnet(QString,QString,int);
    void closeconnect(QString,QString,int);

    void time_get();
    void get_move(QPoint);
    void showMax();
    void showMin();
    void showSkinWidget();
    void setPicName(QString);

    void showmess(QString);
};

#endif // MAINWIDGET_H
