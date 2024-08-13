#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QImage>
#include <QPixmap>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QIcon>
#include <QAction>
#include <QFileInfo>
#include <QStringList>
#include <QDebug>
#include <QTimer>
#include <QCursor>
#include <QTextBrowser>
#include <QMovie>
#include <QStyle>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
public:
    QSystemTrayIcon *trayIcon;
private slots:
    void stTrayIconActive(QSystemTrayIcon::ActivationReason acReason);
    void on_pushButton_clicked();

    void on_label_linkHovered(const QString &link);

private:
    Ui::Widget *ui;
    QMovie *movie;

private:
    QStringList *List2Print;

   // bool eventFilter(QObject *wcg, QEvent *event);//事件过滤

private:
    void QTimerTest();
};
#endif // WIDGET_H
