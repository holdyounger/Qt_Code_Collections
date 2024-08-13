// ArrowWidget.cpp
#include "qarrowwidget.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QPoint>
#include <QPainter>
#include <QImage>
#include <QVariant>
#include <QPropertyAnimation>
ArrowWidget::ArrowWidget(QWidget *parent):
    QWidget(parent),
    m_offset(50),
    m_triangleWidth(TRIANGLE_WIDTH),
    m_triangleHeight(TRIANGLE_HEIGHT)
{

    mainWidget = new QWidget;
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    MainLayout = new QGridLayout();

    lb_text = new QLabel();
    lb_Icon = new QLabel();

    lb_text->setAlignment(Qt::AlignTop);
    lb_text->setStyleSheet("padding: 8px 16px 8px 16px;");

    lb_Icon->setPixmap(QPixmap::fromImage(QImage(":/img/icon1.png")));

    // lb_Icon->setText(QString("测试文本"));

    MainLayout->addWidget(lb_Icon,0,0);
    MainLayout->addWidget(lb_text,0,1);

    mainWidget->setLayout(MainLayout);

    //设置具体阴影
    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(0, 0);
    shadow_effect->setColor(QColor(0, 133, 255));
    shadow_effect->setBlurRadius(5);
    this->setGraphicsEffect(shadow_effect);
}

// 设置小三角显示的起始位置;
void ArrowWidget::setStartPos(int startX)
{
    m_offset = startX;
    repaint();
}
void ArrowWidget::setTriangleInfo(int width, int height)
{
    m_triangleWidth = width;
    m_triangleHeight = height;
}


void ArrowWidget::setText(QString s)
{
    lb_text->setText(s);
    adjustSize();
}

void ArrowWidget::setDerection(ArrowWidget::Derection d)
{
    derect = d;
}

QString ArrowWidget::text()
{
    return lb_text->text();
}

void ArrowWidget::myMove(int x, int y)
{
    int top_left_x, top_left_y;
    switch (derect) {
    case down:
        top_left_x = x - m_offset - m_triangleWidth / 2 - lb_text->x();
        top_left_y = y - m_triangleHeight - lb_text->height() - lb_text->y();
        move(QPoint(top_left_x, top_left_y));
        break;
    case up:
        top_left_x = x - m_offset - m_triangleWidth / 2 - lb_text->x();
        top_left_y = y + m_triangleHeight - lb_text->y();
        move(QPoint(top_left_x, top_left_y));
        break;
    case left:
        top_left_x = x + m_triangleHeight - lb_text->x();
        top_left_y = y - m_offset - m_triangleWidth / 2 - lb_text->y();
        move(QPoint(top_left_x, top_left_y));
        break;
    case right:
        top_left_x = x - m_triangleHeight - lb_text->width() - lb_text->x();
        top_left_y = y - m_triangleWidth / 2 - m_offset - lb_text->y();
        move(QPoint(top_left_x, top_left_y));
        break;
    default:
        break;
    }

}

void ArrowWidget::addCustWidget(QWidget *widget, int row, int column, Qt::Alignment alignment)
{
    MainLayout->addWidget(widget,row,column,alignment);
}


void ArrowWidget::paintEvent(QPaintEvent*)
{
    lb_text->adjustSize();
    mainWidget->setFixedSize(lb_text->width(), lb_text->height());

    QPainter painter(this);
    QPainterPath drawPath;

    painter.setRenderHint(QPainter::Antialiasing, true);
    // painter.setPen(QPen(Qt::blue, 1));
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::white);

    // 小三角区域;
    QPolygon trianglePolygon;

    QRect myRect(mainWidget->x(), mainWidget->y(), mainWidget->width(), mainWidget->height());

    // 设置小三的具体位置
    int tri_pos_x, tri_pos_y;

    m_offset = mainWidget->width() / 2;
    switch (derect)
    {
    case up:{
        // 小三角左边的点的位置
        tri_pos_x = myRect.x() + m_offset;
        tri_pos_y = myRect.y();
        trianglePolygon << QPoint(tri_pos_x, tri_pos_y); // 小三角起点
        trianglePolygon << QPoint(tri_pos_x + m_triangleWidth, tri_pos_y);
        trianglePolygon << QPoint(tri_pos_x + m_triangleWidth / 2, tri_pos_y - m_triangleHeight);
    }
        break;
    case left:{
        // 小三上边点的位置
        tri_pos_x = myRect.x();
        tri_pos_y = myRect.y() + m_offset;
        trianglePolygon << QPoint(tri_pos_x, tri_pos_y);
        trianglePolygon << QPoint(tri_pos_x - m_triangleHeight, tri_pos_y + m_triangleWidth / 2);
        trianglePolygon << QPoint(tri_pos_x, tri_pos_y + m_triangleWidth);
    }
        break;
    case right:{
        // 小三上边点的位置
        tri_pos_x = myRect.x() + myRect.width();
        tri_pos_y = myRect.y() + m_offset;
        trianglePolygon << QPoint(tri_pos_x, tri_pos_y);
        trianglePolygon << QPoint(tri_pos_x + m_triangleHeight, tri_pos_y + m_triangleWidth / 2);
        trianglePolygon << QPoint(tri_pos_x, tri_pos_y + m_triangleWidth);
    }

        break;
    case down:{
        // 小三左边点的位置
        tri_pos_x = myRect.x() + m_offset;
        tri_pos_y = myRect.y() + myRect.height();
        trianglePolygon << QPoint(tri_pos_x, tri_pos_y);
        trianglePolygon << QPoint(tri_pos_x + m_triangleWidth / 2, tri_pos_y + m_triangleHeight);
        trianglePolygon << QPoint(tri_pos_x + m_triangleWidth, tri_pos_y);
    }
        break;
    default:
        break;
    }
    drawPath.addRoundedRect(myRect, BORDER_RADIUS, BORDER_RADIUS);
    drawPath.addPolygon(trianglePolygon);
    painter.drawPath(drawPath);


}


void ArrowWidget::mousePressEvent(QMouseEvent *)
{
    // this->close ();
}

