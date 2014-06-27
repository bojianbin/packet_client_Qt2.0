#ifndef FIRST_ITEM_PRE_H
#define FIRST_ITEM_PRE_H
#include<QWidget>
#include<QtWidgets>
class item_pre:public QDialog
{
    Q_OBJECT
public:

    QLabel *label1;
    QLabel *label2;
    QLineEdit *edit1;
    QLineEdit *edit2;
    QPushButton *button;


    item_pre(QWidget* = 0);
    ~item_pre();
};


#endif // FIRST_ITEM_PRE_H
