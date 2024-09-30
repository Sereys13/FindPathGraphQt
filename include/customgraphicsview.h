
#ifndef CUSTOMGRAPHICSVIEW_H
#define CUSTOMGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QRandomGenerator>
#include <QThread>
#include <QObject>
#include <QPainterPath>
#include <vector>
#include <QMutex>
#include "graph.h"
#include "customrectitem.h"
#include "dfsworker.h"
#include "bfsworker.h"


class CustomGraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    CustomGraphicsView(QWidget *parent = nullptr);
    ~CustomGraphicsView();
    void setDefaultFields();
    void createScene(int row, int col);

protected:
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent * event) override;


private:
    bool flagLetter = false;
    QPointF APos;
    QPointF BPos;
    QGraphicsScene* scene;
    QRandomGenerator random;
    QGraphicsItemGroup* group1;
    QGraphicsItemGroup* group2;
    QThread* bfsThread = new QThread();
    QThread* dfsThread = new QThread();
    const int cellWidth = 200;
    const int cellHeight = 200;
    const int sizeText = 150;
    Graph* gr;
    std::vector<QPointF> pathWay;
    QColor color;
    volatile bool flagWay = false;
    QMutex mutexWay;
    volatile bool flagFind = false;
    QMutex mutexFind;
    void createTextItem(const QString& text, const QPointF& position);
    void createWay();

signals:
    void signalGrayColor();
    void signalLetter();
    void signalBorder();
    void signalNoWay();


};

#endif // CUSTOMGRAPHICSVIEW_H
