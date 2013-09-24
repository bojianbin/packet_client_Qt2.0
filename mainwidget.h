#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QtGui/QWidget>

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
    QTimer *time;
    double times;
    QPoint begin;
    QString bkPicName;
    QPoint normalTopLeft;
private slots:
    void time_get();
    void get_move(QPoint);
    void showMax();
    void showMin();
    void showSkinWidget();
    void setPicName(QString);
};

#endif // MAINWIDGET_H
