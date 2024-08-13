#include "qfloatwidget.h"
#include "ui_qfloatwidget.h"

#include <QGraphicsDropShadowEffect>
#include <QHBoxLayout>
#include <QPoint>
#include <QPainter>
#include <QImage>
#include <QVariant>
#include <QPropertyAnimation>

qFloatWidget::qFloatWidget(QWidget *parent) :
    QWidget(parent),
    m_offset(50),
    m_triangleWidth(TRIANGLE_WIDTH),
    m_triangleHeight(TRIANGLE_HEIGHT),
    ui(new Ui::qFloatWidget)
{
    ui->setupUi(this);
    //设置具体阴影
    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect();
    shadow_effect->setOffset(0, 0);
    shadow_effect->setColor(QColor(0, 133, 255));
    shadow_effect->setBlurRadius(8);
    this->setGraphicsEffect(shadow_effect);


    setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground,true);
}

qFloatWidget::~qFloatWidget()
{
    delete ui;
}

void qFloatWidget::setStartPos(int startX)
{
    m_offset = startX;
    repaint();
}

void qFloatWidget::setTriangleInfo(int width, int height)
{
    m_triangleWidth = width;
    m_triangleHeight = height;
}

void qFloatWidget::setDerection(Derection d)
{
    derect = d;
}

void qFloatWidget::myMove(int x, int y)
{
    int top_left_x, top_left_y;
    switch (derect) {
    case down:
        top_left_x = x - m_offset - m_triangleWidth / 2 - ui->stackedWidget->x();
        top_left_y = y - m_triangleHeight - ui->stackedWidget->height() - ui->stackedWidget->y();
        move(QPoint(top_left_x, top_left_y));
        break;
    case up:
        top_left_x = x - m_offset - m_triangleWidth / 2 - ui->stackedWidget->x();
        top_left_y = y + m_triangleHeight - ui->stackedWidget->y();
        move(QPoint(top_left_x, top_left_y));
        break;
    case left:
        top_left_x = x + m_triangleHeight - ui->stackedWidget->x();
        top_left_y = y - m_offset - m_triangleWidth / 2 - ui->stackedWidget->y();
        move(QPoint(top_left_x, top_left_y));
        break;
    case right:
        top_left_x = x - m_triangleHeight - ui->stackedWidget->width() - ui->stackedWidget->x();
        top_left_y = y - m_triangleWidth / 2 - m_offset - ui->stackedWidget->y();
        move(QPoint(top_left_x, top_left_y));
        break;
    default:
        break;
    }

}

void qFloatWidget::setWidgetIndex(int i)
{
    ui->stackedWidget->setCurrentIndex(i);
}

void qFloatWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPainterPath drawPath;

    painter.setRenderHint(QPainter::Antialiasing, true);
    // painter.setPen(QPen(Qt::blue, 1));
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::white);

    // 小三角区域;
    QPolygon trianglePolygon;

    QRect myRect(ui->stackedWidget->x(), ui->stackedWidget->y(), ui->stackedWidget->width(), ui->stackedWidget->height());

    // 设置小三的具体位置
    int tri_pos_x, tri_pos_y;

    m_offset = ui->stackedWidget->width() / 2  - m_triangleWidth / 2;
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
