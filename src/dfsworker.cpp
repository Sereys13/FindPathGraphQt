#include "dfsworker.h"


DFSWorker::DFSWorker()
{

}

DFSWorker::DFSWorker(Graph* inGr, QPointF inStart, QPointF inFinish)
    : gr(inGr), startPoint(inStart), finish(inFinish){

}

void DFSWorker::newWorker(Graph *inGr, QPointF inStart, QPointF inFinish){
    gr = inGr;
    startPoint = inStart;
    finish = inFinish;
}



void DFSWorker::run(){
    std::set<QPointF> visitedSet;
    std::vector<QPointF> pathDFS;
    if (gr->DFS(startPoint, finish, visitedSet, pathDFS)) {
        emit dfsFinished(pathDFS);
    }
}
