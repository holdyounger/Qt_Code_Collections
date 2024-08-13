#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
