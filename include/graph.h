#ifndef GRAPH_H
#define GRAPH_H

#include <QPointF>
#include <QObject>
#include <set>
#include <vector>
#include <queue>
#include <stack>
#include <utility>
#include <map>

#include <QDebug>

class Graph : public QObject
{
    Q_OBJECT
public:
    Graph();
    Graph(int inRow, int inCol);
    std::vector<std::vector<bool>>& getGrid();
    void newGraph(int inRow, int inCol);
    bool DFS(QPointF start, QPointF finish, std::set<QPointF> &visited, std::vector<QPointF>& pathDFS);
    bool BFS(QPointF start, QPointF finish, std::set<QPointF> &visited, std::vector<QPointF>& pathBFS);

private:
    int row, col;
    std::vector<std::vector<bool>> grid;

public slots:
    void runDFS(QPointF start, QPointF finish);
    void runBFS(QPointF start, QPointF finish);

signals:
    void finishDFS(const std::vector<QPointF>& path);
    void finishBFS(const std::vector<QPointF>& path);
};

#endif // GRAPH_H
