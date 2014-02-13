#ifndef TOOLBUTTON_H
#define TOOLBUTTON_H

#include <QWidget>

class toolButton : public QWidget
{
    Q_OBJECT
public:
    explicit toolButton(QString picName,QString text,QWidget *parent = 0);
    
signals:
    void myToolClicked();

public slots:
    void first_bk();
private:
    bool pressed;
    void setBkPalette(int);

protected:
    void paintEvent(QPaintEvent *);
    void enterEvent(QEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void leaveEvent(QEvent *);
};

#endif // TOOLBUTTON_H
