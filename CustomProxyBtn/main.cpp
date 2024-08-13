#include "QCancelLogin.h"
#include "qmainwidget.h"

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTabWidget>

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(qrc);
    QApplication app(argc, argv);
    QMainWidget widget;
    widget.show();

//    QTabWidget *tabWidget = new QTabWidget;

//     QGraphicsScene scene;
//     QGraphicsProxyWidget *proxy = scene.addWidget(tabWidget);

//     QGraphicsView view(&scene);
//     view.show();

    return app.exec();
}
