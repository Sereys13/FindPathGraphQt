#include "graph.h"

bool operator<(const QPointF &p1, const QPointF &p2) {
    if (p1.x() != p2.x())
        return p1.x() < p2.x();
    return p1.y() < p2.y();
}

Graph::Graph(){
}

Graph::Graph(int inRow, int inCol) : row(inRow), col(inCol){
    grid.resize(inRow, std::vector<bool>(inCol, false));
}

std::vector<std::vector<bool>>& Graph::getGrid(){
    return grid;
}

void Graph::newGraph(int inRow, int inCol){
    row = inRow;
    col = inCol;
    grid.clear();
    grid.resize(inRow, std::vector<bool>(inCol, false));
}

bool Graph::DFS(QPointF start, QPointF finish, std::set<QPointF> &visited, std::vector<QPointF>& pathDFS){
    std::stack<QPointF> st;
    st.push(start);
    std::map<QPointF, QPointF> parent;
    parent[start] = QPointF(-1, -1);
    visited.insert(start);

    while(!st.empty()){
        QPointF current = st.top();
        st.pop();
        if (current == finish){
            for (auto step = current; step != QPointF(-1, -1); step = parent[step]) {
                pathDFS.push_back(step);
            }
            return true;
        }

        std::vector<QPointF> neighbors = {
            QPointF(current.x(), current.y() + 1),
            QPointF(current.x(), current.y() - 1),
            QPointF(current.x() + 1, current.y()),
            QPointF(current.x() - 1, current.y())
        };

        int x;
        int y;
        for (const auto& neighbor : neighbors){
            x = neighbor.x();
            y = neighbor.y();
            if (x <= 0 || x > col || y <= 0 || y > row){
                continue;
            }

            if (grid[y-1][x-1] || visited.count(neighbor)){
                continue;
            }
            st.push(neighbor);
            parent[neighbor] = current;
            visited.insert(neighbor);
        }
    }
    return false;
}

bool Graph::BFS(QPointF start, QPointF finish, std::set<QPointF> &visited, std::vector<QPointF>& pathBFS){
    std::queue<QPointF> que;
    que.push(start);
    std::map<QPointF, QPointF> parent;
    parent[start] = QPointF(-1, -1);
    visited.insert(start);

    while(!que.empty()){
        QPointF current = que.front();
        que.pop();
        if (current == finish){
            for (auto step = current; step != QPointF(-1, -1); step = parent[step]) {
                pathBFS.push_back(step);
            }
            return true;
        }

        std::vector<QPointF> neighbors = {
            QPointF(current.x(), current.y() + 1),
            QPointF(current.x(), current.y() - 1),
            QPointF(current.x() + 1, current.y()),
            QPointF(current.x() - 1, current.y())
        };

        int x;
        int y;
        for (const auto& neighbor : neighbors){
            x = neighbor.x();
            y = neighbor.y();
            if (x <= 0 || x > col || y <= 0 || y > row){
                continue;
            }

            if (grid[y-1][x-1] || visited.count(neighbor)){
                continue;
            }
            que.push(neighbor);
            parent[neighbor] = current;
            visited.insert(neighbor);
        }
    }
    return false;
}

void Graph::runDFS(QPointF start, QPointF finish){
    std::set<QPointF> visited;
    std::vector<QPointF> pathDFS;
    if (DFS(start, finish, visited, pathDFS)){
        emit finishDFS(pathDFS);
    } else {
        emit finishDFS({});
    }
}

void Graph::runBFS(QPointF start, QPointF finish){
    std::set<QPointF> visitedSet;
    std::vector<QPointF> pathBFS;
    if (BFS(start, finish, visitedSet, pathBFS)){
        emit finishBFS(pathBFS);
    } else {
        emit finishBFS({});
    }
}


