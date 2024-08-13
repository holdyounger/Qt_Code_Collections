#include "QCancelLogin.h"
#include "QCustomWidgetProxy.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMutex>
#include <QDebug>

QCancelLogin* QCancelLogin::m_InstanceBtn = nullptr;

QCancelLogin::QCancelLogin(QWidget *parent) : QWidget(parent)
{
    m_CanelLoginBtn = new QPushButton;
    m_CanelLoginBtn->setAttribute(Qt::WA_TranslucentBackground);
    m_CanelLoginBtn->setWindowFlags(Qt::FramelessWindowHint);
    // m_CanelLoginBtn->setIcon(QIcon(QString(":/icon_unqualified.png")));
    m_CanelLoginBtn->setStyleSheet(QString("QPushButton {border-image: url(:/icon_unqualified.png);} .QToolTip {font-family: \"Microsoft YaHei\";font-size: 12px;color: #F2F2F2;text-align: center;border: none;background-color: #000000;} "));
    m_CanelLoginBtn->setFixedSize(QSize(40, 40));
    //  m_CanelLoginBtn->setIcon(QIcon());
    connect(m_CanelLoginBtn, &QPushButton::clicked, this, &QCancelLogin::slotLoginBtnClick);

    QCustomWidgetProxy* proxy = new QCustomWidgetProxy(0, Qt::SubWindow);
	proxy->setWidget(m_CanelLoginBtn);
    proxy->setCacheMode(QGraphicsItem::DeviceCoordinateCache);

	scene = new QGraphicsScene;
	scene->setStickyFocus(true);
    scene->addItem(proxy);
    QRectF rf = scene->itemsBoundingRect();
    rf.setWidth(rf.width()+5);
    rf.setHeight(rf.height()+5);
    scene->setSceneRect(rf.toAlignedRect());

    m_View = new QGraphicsView(scene);
    m_View->scale(0.5, 0.5);
	m_View->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_View->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_View->setRenderHints(m_View->renderHints() | QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    m_View->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    // m_View->setResizeAnchor(QGraphicsView::AnchorUnderMouse);
    // m_View->setTabletTracking(false);  // 禁用默认变换
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);


    UpdateFormText();
}

QCancelLogin *QCancelLogin::GetInstance()
{
	if (!m_InstanceBtn) {
		QMutex mutex;
		mutex.lock();

		if (!m_InstanceBtn)
			m_InstanceBtn = new QCancelLogin;

		mutex.unlock();
	}

	return m_InstanceBtn;
}

void QCancelLogin::slotLoginBtnClick()
{
	qDebug() << __FUNCTION__ << __LINE__;
}

void QCancelLogin::UpdateFormText()
{
    m_CanelLoginBtn->setToolTip(tr("取消登录"));
}

QGraphicsView* QCancelLogin::GetView()
{
	return m_View;
}

namespace CancelBtn
{
	QCancelLogin* Get()
	{
		return QCancelLogin::GetInstance();
	}

	QGraphicsView* GetView()
	{
		return QCancelLogin::GetInstance()->GetView();
	}

}
