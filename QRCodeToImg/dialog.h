#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPainter>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

protected:
    void paintEvent(QPaintEvent *);
private:
    Ui::Dialog *ui;
};
#endif // DIALOG_H
