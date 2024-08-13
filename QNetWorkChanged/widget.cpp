#include "widget.h"
#include "ui_widget.h"
#include <QNetworkConfiguration>
#include <QNetworkAccessManager>
#include <QDebug>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QNetworkAccessManager *mConfManager = new QNetworkAccessManager;
    QList<QNetworkConfiguration> activeConfigs = mConfManager->allConfigurations(QNetworkConfiguration :: Active);
    qDebug() << "isonline：" << mConfManager-> isOnline();
}

Widget::~Widget()
{
    delete ui;
}

