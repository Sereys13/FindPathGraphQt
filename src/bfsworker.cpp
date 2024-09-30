#include "bfsworker.h"

BFSWorker::BFSWorker()
{

}

BFSWorker::BFSWorker(Graph* inGr, QPointF inStart, QPointF inFinish)
    : gr(inGr), startPoint(inStart), finish(inFinish){

}

void BFSWorker::newWorker(Graph *inGr, QPointF inStart, QPointF inFinish){
    gr = inGr;
    startPoint = inStart;
    finish = inFinish;
}

void BFSWorker::run(){
    std::set<QPointF> visitedSet;
    std::vector<QPointF> pathDFS;
    if (gr->BFS(startPoint, finish, visitedSet, pathDFS)) {
        emit bfsFinished(pathDFS);
    }
}
