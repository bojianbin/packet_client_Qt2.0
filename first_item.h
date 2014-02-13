#ifndef FIRST_ITEM_H
#define FIRST_ITEM_H

#include <QWidget>
#include<QtGui>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
private:
    QString label;
    QString ip;
    QString port;

    QLabel *text;
    QPushButton *dele;
    QPushButton *find;
    QComboBox *box;
    QPushButton * start;
    QPushButton * stop;

    void settpalette(int p);
signals:
    void closeconnect(QString,QString,int);
    void startconnect(QString ,QString ,int );
    void stopconnect(QString,QString,int);
    void findconnect(QString,QString,int);
public slots:
    void changetext(QString);
    void changelabel(QString ,QString );
private slots:
    void startenter();
    void stopenter();
    void findenter();
    void closeenter();
protected:
    void closeEvent(QCloseEvent *);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void paintEvent(QPaintEvent *);
};




#endif // FIRST_ITEM_H
