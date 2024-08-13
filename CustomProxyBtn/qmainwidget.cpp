#include "qmainwidget.h"
#include "ui_qmainwidget.h"
#include "QCancelLogin.h"
#include "QCustomWidgetProxy.h"
#include <QGraphicsSceneWheelEvent>
#include <QDebug>

QMainWidget::QMainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QMainWidget)
{
    ui->setupUi(this);

    // code
    ui->gridLayout->addWidget(CancelBtn::GetView());

    // gui
    loginWidget = new QPushButton;

    loginWidget->setFixedSize(QSize(40, 40));
    loginWidget->setStyleSheet(QString("border-image: url(:/icon_unqualified.png);"));

    loginWidget->installEventFilter(this);
	ui->gridLayout_5->addWidget(loginWidget);

    QPushButton *btn = new QPushButton;
    btn->setText(tr("取消登录"));
    // loginWidget->setIcon(QIcon(QString(":/icon_unqualified.png")));
    btn->setFixedSize(QSize(40,40));
    btn->installEventFilter(this);
    btn->setStyleSheet(QString("border-image: url(:/icon_unqualified.png);"));
    btn->show();

    QCustomWidgetProxy *proxy = new QCustomWidgetProxy(0, Qt::Window);
    proxy->setWidget(btn);
    proxy->setCacheMode(QGraphicsItem::ItemCoordinateCache);

    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setStickyFocus(true);
    scene->addItem(proxy);

    scene->setSceneRect(scene->itemsBoundingRect());

    qDebug() << "scene" << scene->sceneRect();

    ui->graphicsView->setScene(scene);
    ui->graphicsView->installEventFilter(this);
    // ui->graphicsView->setFocusPolicy( Qt::NoFocus );
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // ui->graphicsView->scale(0.5, 0.5);
    ui->graphicsView->setRenderHints(ui->graphicsView->renderHints() | QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    ui->graphicsView->show();

}

QMainWidget::~QMainWidget()
{
    delete ui;
}


bool QMainWidget::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::GraphicsSceneWheel)
    {
        ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        double scaleFactor = 1.15;
        bool ok = QApplication::keyboardModifiers() & Qt::ControlModifier;
        if (ok)
        {
            QGraphicsSceneWheelEvent *scrollevent = static_cast<QGraphicsSceneWheelEvent *>(event);
            if (scrollevent->delta() > 0)
            {
                ui->graphicsView->scale(scaleFactor, scaleFactor);
            }
            else
            {
                ui->graphicsView->scale(1/scaleFactor, 1/scaleFactor);
            }
        }

        event->accept();
        return true;
    }

    if (obj == loginWidget)
    {
        qDebug() << event;

        if (event->type() == QEvent::Enter)
        {
			loginWidget->setFixedSize(QSize(60, 60));
        }
        else if (event->type() == QEvent::Leave)
        {
			loginWidget->setFixedSize(QSize(40, 40));
        }

		event->accept();
		return true;
    }
    return false;
}
