#ifndef TITLEWIDGET_H
#define TITLEWIDGET_H

#include <QWidget>

class myPushButton;
class sysButton;

class titleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit titleWidget(QWidget *parent = 0);
    
signals:
    void showMin();
    void showMax();
    void move(QPoint);

    void showSkin();

public slots:

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent *);

private:
    QPoint pressedPoint;
QPoint tmp;
    bool isMove;

    myPushButton *btnSkin;
    sysButton *btnMenuBar;
    sysButton *btnMin;
    sysButton *btnMax;
    sysButton *btnClose;
};

#endif // TITLEWIDGET_H
