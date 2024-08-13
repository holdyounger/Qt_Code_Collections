#ifndef QMYLABEL_H
#define QMYLABEL_H

#include <QObject>
#include <QLabel>

class QMyLabel : public QLabel
{
    Q_OBJECT
public:
    explicit QMyLabel(QWidget *parent = nullptr);
    ~QMyLabel();

signals:
    void sigShow();
    void sigHide();

public slots:

public:
    void enterEvent(QEvent * event);
    void leaveEvent(QEvent * event);
};

#endif // QMYLABEL_H
