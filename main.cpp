#include <QtGui/QApplication>
#include "mainwidget.h"
#include <QTextCodec>
#include"statuswidget.h"
#include "titlewidget.h"
#include"toolwidget.h"
#include<QtGui>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);

    QPalette palette;
    palette.setColor(QPalette::WindowText,Qt::white);
    a.setPalette(palette);

    a.setWindowIcon(QIcon( ":/icon/penguintvicon.png"));
    mainWidget w;
    w.show();


    return a.exec();
}
