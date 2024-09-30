#include "customrectitem.h"

CustomRectItem::CustomRectItem(qreal x, qreal y, qreal width, qreal height)
    : QGraphicsRectItem(x, y, width, height), hoverTimer(new QTimer(this)), hoverTime(0) {
    setAcceptHoverEvents(true);
    pos = QPointF(x + width/2,y + height/2);
    QObject::connect(hoverTimer, &QTimer::timeout, this, [=](){
        hoverTime += 100;
        if (hoverTime >= 1500) {
            if (brush().color() == Qt::white){
                emit signalTimer(pos);
            }
            hoverTimer->stop();
        }
    });
}

CustomRectItem::~CustomRectItem(){
    emit signalDelete();
}

void CustomRectItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    Q_UNUSED(event);
    hoverTimer->stop();
    if (brush().color() == Qt::white){
        emit signalExit();
    }
}

void CustomRectItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    Q_UNUSED(event);
    hoverTime = 0;
    hoverTimer->start(100);
}


