#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include<QPropertyAnimation>

#include <QGraphicsEffect>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_widget = new qFloatWidget();
    ui->label->installEventFilter(this);
}

Widget::~Widget()
{
    delete ui;
}


bool Widget::eventFilter(QObject *obj, QEvent *event)
{
    QString str = QString("<style> span {text-decoration: none; color: #006FFF;font-family: Microsoft YaHei;}</style>  <span>连接%1</span> <br> 虚拟地址：%2<br>登录地址：%3").arg("已成功").arg("192.168.0.0").arg("192.168.0.1");

    static int x = 0;
    static int y = 0;
    static uint8_t flag=0;
    if(obj == ui->label)
    {
        if(event->type() == QEvent::Enter)
        {
            ui->label->setText("进入");
            QPoint GlobalPoint(ui->label->mapToGlobal(QPoint(0, 0)));//获取控件在窗体中的坐标
            x = GlobalPoint.x();
            y = GlobalPoint.y() + ui->label->height();

            qDebug() << x << ":" << y ;
            m_widget->myMove(x, y);
            m_widget->setDerection(qFloatWidget::up);
            m_widget->show();
        }
        else if(event->type() == QEvent::Leave)
        {
            ui->label->setText(("离开"));
            m_widget->hide();
        }
    }

    // 添加动画
    // 位移
    QPropertyAnimation *pPosAnimation1 = new QPropertyAnimation(m_widget, "pos");
    pPosAnimation1->setDuration(1000);
    pPosAnimation1->setStartValue(QCursor::pos());
    pPosAnimation1->setEndValue(QPoint(x,y));
    pPosAnimation1->setEasingCurve(QEasingCurve::InOutQuad);
    pPosAnimation1->start();
    return QWidget::eventFilter(obj,event);
}

