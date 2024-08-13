#include "qeventtest.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QEventTest w;
    w.show();
    return a.exec();
}
