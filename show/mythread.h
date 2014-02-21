#ifndef THREAD_H
#define THREAD_H
#include<QThread>
#include<QMutex>
#include<sys/types.h>
#include"bo.h"
class mythread :public QThread
{
    Q_OBJECT
public:

    mythread();
    void setprot(QString,QString);
    void stopp();

public slots:
    void heart_beat();//100ms的定时
signals:
    void showmess(QString);
protected:
    void run();
public:
    int sockfd;
    char *ip;
    int port;

    bool stop_thread;
    QMutex stop_lock;

    uint8_t *ready;
    int size;
    bool ready_to_go;//ready中有有效的数据
    QMutex ready_lock;



    int heart;
    int ask;//客户端"请求报文"重发的计时
    int resend;//”重新发送“报文的计时
    QMutex time_lock;
};


#endif // THREAD_H
