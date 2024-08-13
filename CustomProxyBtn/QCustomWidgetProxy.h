#ifndef CUSTOMPROXY_H
#define CUSTOMPROXY_H

#include <QTimeLine>
#include <QGraphicsProxyWidget>

class QCustomWidgetProxy : public QGraphicsProxyWidget
{
    Q_OBJECT

public:
    explicit QCustomWidgetProxy(QGraphicsItem *parent = 0, Qt::WindowFlags wFlags = 0);

    QRectF boundingRect() const override;
    void paintWindowFrame(QPainter *painter, const QStyleOptionGraphicsItem *option,
                          QWidget *widget) override;

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    bool sceneEventFilter(QGraphicsItem *watched, QEvent *event) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

private slots:
    void updateStep(qreal step);
    void stateChanged(QTimeLine::State);
    void zoomIn();
    void zoomOut();

private:
    QTimeLine *timeLine;
    bool popupShown;
    QGraphicsItem *currentPopup;
};

#endif // CUSTOMPROXY_H
