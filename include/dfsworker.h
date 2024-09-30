#ifndef DFSWORKER_H
#define DFSWORKER_H

#include <QObject>
#include <QThread>
#include <QPointF>
#include "graph.h"

class DFSWorker : public QThread
{
    Q_OBJECT
public:
    DFSWorker();
    DFSWorker(Graph* inGr, QPointF inStart, QPointF inFinish);
    void newWorker(Graph* inGr, QPointF inStart, QPointF inFinish);

protected:
    void run() override;

private:
    Graph* gr;
    QPointF startPoint;
    QPointF finish;

signals:
    void dfsFinished(const std::vector<QPointF> &path);
};

#endif // DFSWORKER_H
