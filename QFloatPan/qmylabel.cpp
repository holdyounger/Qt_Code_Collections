#include "qmylabel.h"
#include <QDebug>

QMyLabel::QMyLabel(QWidget *parent)
{
    this->setMouseTracking(true);
}

QMyLabel::~QMyLabel()
{

}
void QMyLabel::enterEvent(QEvent * event)
{
    qDebug() << "show()";
    emit sigShow();
    QLabel::enterEvent(event);
}

void QMyLabel::leaveEvent(QEvent * event)
{
    qDebug() << "hide()";
    emit sigHide();
    QLabel::leaveEvent(event);
}
