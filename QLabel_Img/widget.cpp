#include "widget.h"
#include "ui_widget.h"

#include <QLatin1String>

#if defined(_MSC_VER) && (_MSC_VER >= 1600)
#pragma execution_character_set("utf-8")
#endif

#define TEXT_COLOR_RED(STRING)         "<font color=red>" + STRING + "</font>" "<font color=black> </font>"
#define TEXT_COLOR_BLUE(STRING)        "<font color=blue>" + STRING + "</font>" "<font color=black> </font>"
#define TEXT_COLOR_GREEN(STRING)        "<font color=green>" + STRING + "</font>" "<font color=black> </font>"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //    setStyleSheet(QString("QWidget:hover {"
    //                          "border: 2px solid #308BFF;"
    //                          "}"));
    //setMouseTracking(true);

    ui->toolButton->setIconSize(QSize(106,106));
    ui->toolButton->setIcon(QIcon(":/app_icon2.png"));
    ui->toolButton->setStyleSheet(QString("QToolButton {"
                                          "border: none;"
                                          "border-radius: 4px;"
                                          "}"
                                          "QToolButton:hover {"
                                          "border: 2px solid #308BFF;"
                                          "}"));
    ui->textBrowser->setReadOnly(true);
    QString html = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\np, li { white-space: pre-wrap; }\n</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>";
    ui->textBrowser->setHtml(html);
    ui->textBrowser->setText(QString("测试文本"));



    QFileInfo info(":/Win11.png");

    List2Print = new QStringList;
    List2Print->append("1");
    List2Print->append("2");
    List2Print->append("3");
    List2Print->append("4");


    QPixmap img(":/Win11");
    movie = new QMovie(":/gif_loding.gif");

    ui->label->setMovie(movie);
    movie->start();

    //    ui->label->setPixmap(img);
    //    ui->label->setScaledContents(true);

    ui->label->setToolTip(QString("壁纸《Win11.png》"));
    ui->pushButton->setToolTip(QString("隐藏或显示图片"));

    QIcon icon = QApplication::style()->standardIcon((QStyle::StandardPixmap)0);
    QIcon icon1 = QApplication::style()->standardIcon((QStyle::StandardPixmap)9);


    //设置通知栏的图标
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(icon);

    //设置通知栏的单击事件
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(stTrayIconActive(QSystemTrayIcon::ActivationReason)));

    //设置通知栏的右键菜单
    QMenu * menu = new QMenu();
    //设置菜单项目

    QAction *actionHide = new QAction(icon, "Hide", menu);

    menu->addAction(actionHide);
    trayIcon->setContextMenu(menu);
    // 设置Action的响应
    connect(actionHide, SIGNAL(triggered()), this, SLOT(stActionHide()));
    trayIcon->show();

    //托盘的消息提示
    trayIcon->showMessage("title", "this is a message", icon1);


    // line Edit 焦点
    ui->lineEdit->installEventFilter(this);
    ui->label_2->installEventFilter(this);

}

Widget::~Widget()
{
    delete ui;
}


void Widget::stTrayIconActive(QSystemTrayIcon::ActivationReason acReason)
{
    switch (acReason)
    {
    case QSystemTrayIcon::Trigger:
    {
        showNormal();
        break;
    }
    default:
        ;
    }

}
void Widget::on_pushButton_clicked()
{
    QIcon icon = QApplication::style()->standardIcon((QStyle::StandardPixmap)0);
    QIcon icon1 = QApplication::style()->standardIcon((QStyle::StandardPixmap)9);

    if(ui->label->isVisible())
    {
        trayIcon->showMessage("提醒", "隐藏图片", icon1);
        ui->label->hide();
    }
    else
    {
        trayIcon->showMessage("提醒", "显示图片", icon1);
        ui->label->setVisible(true);
    }

    return ;
    QTimer *timer = new QTimer;
    timer->start(1000);

    int i = List2Print->length() - 1;
    connect(timer, &QTimer::timeout, this, [=]() mutable {
        qDebug() << List2Print->at(i--) << endl;
        if(i < 0)
            i = List2Print->length() - 1;
    });
    //timer->deleteLater();
}

void Widget::QTimerTest()
{
    QTimer *timer = new QTimer;
    connect(timer, &QTimer::timeout, this, [=]()mutable{
        QString content = ui->textBrowser->document()->toPlainText();
        qDebug() << ui->textBrowser->frameGeometry() << QCursor::pos() << endl;
        if(ui->textBrowser->frameGeometry().contains(QCursor::pos()))
        {
            qDebug() << "Enter" << endl;
            ui->textBrowser->setText(TEXT_COLOR_GREEN(content));
        }
        else
        {
            qDebug() << "Enterless" << endl;
            ui->textBrowser->setText(TEXT_COLOR_RED(content));
        }
    });

    timer->start(500);
}


void Widget::on_label_linkHovered(const QString &link)
{
    movie->stop();
    movie->start();
}

