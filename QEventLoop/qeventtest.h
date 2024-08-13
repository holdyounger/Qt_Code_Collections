#ifndef QEVENTTEST_H
#define QEVENTTEST_H

#include <QWidget>
#include <../include.h>

QT_BEGIN_NAMESPACE
namespace Ui { class QEventTest; }
QT_END_NAMESPACE

class QEventTest : public QWidget
{
    Q_OBJECT

public:
    QEventTest(QWidget *parent = nullptr);
    ~QEventTest();

    void test_Block();

private:
    Ui::QEventTest *ui;

    bool m_success;

signals:
    void myfinished();
private slots:
    void on_pushButton_clicked();
};
#endif // QEVENTTEST_H
