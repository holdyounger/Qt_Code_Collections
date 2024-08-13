#include "widget.h"
#include "dialog.h"

#include <QApplication>
#include <QLabel>
#include <QPixmap>
#include <QSplashScreen>
#include <QThread>
#include "cmysplashscreen.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    QPixmap pixmap(":/test.gif");
//    CMySplashScreen splash(pixmap,10);
//    splash.show();
//    QDateTime time = QDateTime::currentDateTime();
//        QDateTime currentTime = QDateTime::currentDateTime();   //记录当前时间
//        while (time.secsTo(currentTime) <= 5)                   //5为需要延时的秒数
//        {
//            currentTime = QDateTime::currentDateTime();
//            a.processEvents();
//        };

    Dialog d;
    d.show();

    QDateTime time = QDateTime::currentDateTime();
    QDateTime currentTime = QDateTime::currentDateTime();   //记录当前时间
    while (time.secsTo(currentTime) <= 5)                   //5为需要延时的秒数
    {
        currentTime = QDateTime::currentDateTime();
        a.processEvents();
    };

    Widget w;
    w.show();


//    splash.finish(&w);

   d.finish(&w);
    return a.exec();

}
