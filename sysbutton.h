#ifndef SYSBUTTON_H
#define SYSBUTTON_H

#include <QPushButton>

class sysButton : public QPushButton
{
    Q_OBJECT
public:
    explicit sysButton(QString picName,QString tipText,QWidget *parent = 0);
    
signals:
    
public slots:
    
private:

    enum buttonStatus{NORMAL,ENTER,PRESS,NOSTATUS};
    buttonStatus status;
    QPixmap pixmap;

    int btnWidth;
    int btnHeight;

protected:
    void paintEvent(QPaintEvent *);
    void enterEvent(QEvent *);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void leaveEvent(QEvent *);
};

#endif // SYSBUTTON_H
