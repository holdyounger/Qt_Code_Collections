#ifndef QCANCELLOGIN_H
#define QCANCELLOGIN_H

#include <QWidget>
#include <QPushButton>
#include <QGraphicsView>

class QCustomWidgetProxy;
class QGraphicsView;
class QGraphicsScene;

class QCancelLogin : public QWidget
{
    Q_OBJECT
public:
    explicit QCancelLogin(QWidget *parent = nullptr);

    static QCancelLogin *GetInstance();

    void UpdateFormText();

    QGraphicsView* GetView();
private:
        

private:
    static QCancelLogin *m_InstanceBtn;

    QPushButton *m_CanelLoginBtn = nullptr;
    QCustomWidgetProxy *m_CustomWidgetProxy = nullptr;
    QGraphicsView* m_View = nullptr;
    QGraphicsScene* scene = nullptr;
signals:

private Q_SLOTS: 
	void slotLoginBtnClick();
};


namespace CancelBtn {
    QCancelLogin* Get();

    QGraphicsView* GetView();
}

#endif // QCANCELLOGIN_H
