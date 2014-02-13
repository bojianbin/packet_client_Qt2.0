#ifndef CONTENTWIDGET_H
#define CONTENTWIDGET_H

#include <QWidget>
#include"first_item.h"

class contentWidget : public QWidget
{
    Q_OBJECT
public:
    explicit contentWidget(QWidget *parent = 0);
    
signals:
    void startconnect(QString,QString,int);
    void findconnect(QString,QString,int);
    void closeconnect(QString,QString,int);
public slots:
private slots:
    void additem();
    void close_item();
private:
    QAction *add;
    QList<Widget*>actionlist;
    QVBoxLayout *mainlayout;
    void addactons();
};

#endif // CONTENTWIDGET_H
