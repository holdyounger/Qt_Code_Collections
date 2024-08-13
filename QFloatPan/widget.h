#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMouseEvent>

#include "qmylabel.h"
#include "qfloatwidget.h"

#if defined(_MSC_VER) && (_MSC_VER >= 1600)
    #pragma execution_character_set("utf-8")
#endif

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    bool eventFilter(QObject *obj, QEvent *event);

private:
    Ui::Widget *ui;
    qFloatWidget *m_widget;
};
#endif // WIDGET_H
