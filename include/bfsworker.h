#ifndef BFSWORKER_H
#define BFSWORKER_H

#include <QObject>
#include <QThread>
#include <QPointF>
#include "graph.h"

class BFSWorker : public QThread
{
    Q_OBJECT
public:
    BFSWorker();
    BFSWorker(Graph* inGr, QPointF inStart, QPointF inFinish);
    void newWorker(Graph* inGr, QPointF inStart, QPointF inFinish);

protected:
    void run() override;

private:
    Graph* gr;
    QPointF startPoint;
    QPointF finish;

signals:
    void bfsFinished(const std::vector<QPointF> &path);
};

#endif // BFSWORKER_H
