#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QNetworkRequest request;
    QNetworkAccessManager* naManager = new QNetworkAccessManager(this);
    QMetaObject::Connection connRet = QObject::connect(naManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(requestFinished(QNetworkReply*)));
    Q_ASSERT(connRet);

    //设置URL
    request.setUrl(QUrl("http://www.baidu.com"));
    //发送get请求
    naManager->get(request);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::requestFinished(QNetworkReply* reply)
{
    // 获取返回状态码
    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if(statusCode.isValid())
    {
       qDebug() << "status code =" << statusCode.toInt();
    }

    QVariant reason = reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
    if(reason.isValid())
    {
        qDebug() << "reason =" << reason.toString();
    }

    QNetworkReply::NetworkError err = reply->error();
    if(err != QNetworkReply::NoError)
    {
        qDebug() << "Failed:" << reply->errorString();
    }
    else
    {
        // 获取返回请求详细信息
        QString ss = "";
        ss.append(reply->readAll());
        qDebug()<<ss.toUtf8();
    }
}
