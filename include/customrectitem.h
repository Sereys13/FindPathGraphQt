#ifndef CUSTOMRECTITEM_H
#define CUSTOMRECTITEM_H

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QPointF>
#include <QObject>
#include <QDebug>

class CustomRectItem : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    CustomRectItem(qreal x, qreal y, qreal width, qreal height);
    ~CustomRectItem();

protected:
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;

private:
    QTimer* hoverTimer;
    int hoverTime;
    QPointF pos;

signals:
    void signalTimer(QPointF pos);
    void signalExit();
    void signalDelete();
};

#endif // CUSTOMRECTITEM_H
