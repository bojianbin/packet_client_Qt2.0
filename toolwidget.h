#ifndef TOOLWIDGET_H
#define TOOLWIDGET_H

#include <QWidget>
class toolButton;
class toolWidget : public QWidget
{
    Q_OBJECT
public:
    toolButton *t2;
    explicit toolWidget(QWidget *parent = 0);
    
signals:
    void click_tool(int);

private:
    int index;
    QVector<toolButton *>list;
private slots:
    void change_index1();
    void change_index2();
    void change_index3();
    void change_index4();
    void change_index5();


};

#endif // TOOLWIDGET_H
