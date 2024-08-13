#ifndef QMAINWIDGET_H
#define QMAINWIDGET_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class QMainWidget;
}

class QMainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QMainWidget(QWidget *parent = nullptr);
    ~QMainWidget();

    bool eventFilter(QObject *obj, QEvent *event);
private:
    Ui::QMainWidget *ui;

    QPushButton *m_CanelLoginBtn = nullptr;
    QPushButton* loginWidget;
};

#endif // QMAINWIDGET_H
