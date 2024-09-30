
#include "customgraphicsview.h"

CustomGraphicsView::CustomGraphicsView(QWidget *parent) : QGraphicsView(parent){
    time_t tt = time(NULL);
    random.seed(tt);
    scene = new QGraphicsScene(this);
    gr = new Graph(10,10);

    QObject::connect(dfsThread, &QThread::started, [this](){
        gr->runDFS(QPointF((APos.x())/cellWidth + 0.5, APos.y()/cellHeight + 0.5), QPointF(BPos.x()/cellWidth + 0.5, BPos.y()/cellHeight + 0.5));
    });

    QObject::connect(bfsThread, &QThread::started, [this](){
        gr->runBFS(QPointF((APos.x())/cellWidth + 0.5, APos.y()/cellHeight + 0.5), QPointF(BPos.x()/cellWidth + 0.5, BPos.y()/cellHeight + 0.5));
    });

    QObject::connect(gr, &Graph::finishDFS, [this](const std::vector<QPointF>& path){
        bfsThread->quit();
        if (!path.empty()){
            mutexWay.lock();
            if (!flagWay){
                pathWay = path;
                color = Qt::red;
                flagWay = true;
            }
            mutexWay.unlock();
        } else {
            emit signalNoWay();
        }

        dfsThread->quit();
    });

    QObject::connect(gr, &Graph::finishBFS, [this](const std::vector<QPointF>& path){
        dfsThread->quit();
        if (path.size() != 0){
            mutexWay.lock();
            if (!flagWay){
                pathWay = path;
                color = Qt::blue;
                flagWay = true;
            }
            mutexWay.unlock();
        } else {
            emit signalNoWay();
        }

        bfsThread->quit();
    });

}

CustomGraphicsView::~CustomGraphicsView(){
    delete bfsThread;
    delete dfsThread;
    setScene(nullptr);
    delete gr;
    delete scene;
}

void CustomGraphicsView::setDefaultFields(){
    flagLetter = false;
    APos = QPointF();
    BPos = QPointF();
}

void CustomGraphicsView::createScene(int h, int w){
    setScene(nullptr);
    delete scene;
    scene = new QGraphicsScene(this);

    scene->setSceneRect(0, 0, w * cellWidth, h * cellHeight);
    gr->newGraph(h, w);
    std::vector<std::vector<bool>>& grid = gr->getGrid();
    QPen blackPen(Qt::black);
    QBrush grayBrush(Qt::gray);
    QBrush whiteBrush(Qt::white);
    int x, y;


    for (int row = 0; row < h; ++row) {
        for (int col = 0; col < w; ++col) {
            x = col * cellWidth;
            y = row * cellHeight;
            bool isObstacle = random.bounded(0, 5) == 1;
            QBrush brush = isObstacle ? grayBrush : whiteBrush;
            grid[row][col] = isObstacle;
            CustomRectItem *rectItem = new CustomRectItem(x, y, cellWidth, cellHeight);
            rectItem->setPen(blackPen);
            rectItem->setBrush(brush);
            DFSWorker* dfsWorker = new DFSWorker();
            BFSWorker* bfsWorker = new BFSWorker();
            QObject::connect(rectItem, &CustomRectItem::signalTimer, [=](QPointF pos){
                if (flagLetter && pos != APos){
                    for (QGraphicsItem* item : group1->childItems()) {
                        delete item;
                    }

                    flagFind = false;
                    dfsWorker->newWorker(gr, QPointF((APos.x())/cellWidth + 0.5, APos.y()/cellHeight + 0.5), QPointF(pos.x()/cellWidth + 0.5, pos.y()/cellHeight + 0.5));
                    connect(dfsWorker, &DFSWorker::dfsFinished, this, [=](const std::vector<QPointF> &pathDFS) {
                        mutexFind.lock();
                        if (!flagFind){
                            flagFind = true;
                            mutexFind.unlock();
                            QPen pen(Qt::red, 25);
                            int offsetW = cellWidth / 2;
                            int offsetH = cellWidth / 2;
                            QPainterPath path;
                            path.moveTo(pathDFS[0].x() * cellWidth - offsetW, pathDFS[0].y() * cellHeight - offsetH);
                            for (size_t i = 1; i < pathDFS.size(); i++) {
                                path.lineTo(pathDFS[i].x() * cellWidth - offsetW, pathDFS[i].y() * cellHeight - offsetH);
                            }
                            QGraphicsPathItem *pathItem = new QGraphicsPathItem(path);
                            pathItem->setPen(pen);
                            group1->addToGroup(pathItem);
                        } else {
                            mutexFind.unlock();
                        }
                    });

                    bfsWorker->newWorker(gr, QPointF((APos.x())/cellWidth + 0.5, APos.y()/cellHeight + 0.5), QPointF(pos.x()/cellWidth + 0.5, pos.y()/cellHeight + 0.5));
                    connect(bfsWorker, &BFSWorker::bfsFinished, this, [=](const std::vector<QPointF> &pathDFS) {
                        mutexFind.lock();
                        if (!flagFind){
                            flagFind = true;
                            mutexFind.unlock();
                            QPen pen(Qt::blue, 25);
                            int offsetW = cellWidth / 2;
                            int offsetH = cellWidth / 2;
                            QPainterPath path;
                            path.moveTo(pathDFS[0].x() * cellWidth - offsetW, pathDFS[0].y() * cellHeight - offsetH);
                            for (size_t i = 1; i < pathDFS.size(); i++) {
                                path.lineTo(pathDFS[i].x() * cellWidth - offsetW, pathDFS[i].y() * cellHeight - offsetH);
                            }
                            QGraphicsPathItem *pathItem = new QGraphicsPathItem(path);
                            pathItem->setPen(pen);
                            group1->addToGroup(pathItem);
                        } else {
                            mutexFind.unlock();
                        }
                    });


                    dfsWorker->start();
                    bfsWorker->start();
                }
            });

            QObject::connect(rectItem, &CustomRectItem::signalExit, [this](){
                for (QGraphicsItem* item : group1->childItems()) {
                    delete item;
                }
            });

            QObject::connect(rectItem, &CustomRectItem::signalDelete, [=](){
                dfsWorker->deleteLater();
                bfsWorker->deleteLater();
            });
            scene->addItem(rectItem);
        }
    }

    group2 = scene->createItemGroup(QList<QGraphicsItem*>());
    group1 = scene->createItemGroup(QList<QGraphicsItem*>());
    group2->setZValue(2);
    group1->setZValue(3);
    setScene(scene);
    scale(0.1, 0.1);
    setDefaultFields();
}


void CustomGraphicsView::wheelEvent(QWheelEvent *event){
    qreal scaleFactor = 1.2;
    if (event->angleDelta().y() < 0) {
        scaleFactor = 1.0 / scaleFactor;
    }

    scale(scaleFactor, scaleFactor);
    event->accept();
}


void CustomGraphicsView::mousePressEvent(QMouseEvent * event){
    if (event->button() == Qt::LeftButton){
        QPointF scenePos = mapToScene(event->pos());
        QList<QGraphicsItem*> itemsAtPoint = scene->items(scenePos);
        uint8_t count = 0;
        qreal zValue;
        for (QGraphicsItem* item : itemsAtPoint) {
            zValue = item->zValue();
            if (zValue == 0) {
                count++;
                if (count == 3){
                    emit signalBorder();
                    return;
                }
            }
        }

        for (QGraphicsItem *item : itemsAtPoint) {
            if (auto *rectItem = qgraphicsitem_cast<QGraphicsRectItem*>(item)) {
                QColor color = rectItem->brush().color();
                QRectF rect = rectItem->rect();
                if (color == Qt::white) {
                    if (!flagLetter){
                        for (QGraphicsItem* item : group2->childItems()) {
                            delete item;
                        }

                        createTextItem("A",rect.center());
                        APos = rect.center();
                        flagLetter = true;
                        group1->setVisible(true);
                    } else {
                        createTextItem("B",rect.center());
                        BPos = rect.center();
                        flagLetter = false;
                        group1->setVisible(false);
                        createWay();
                    }
                    break;
                } else if (color == Qt::gray){
                    emit signalGrayColor();
                    break;
                }
            } else if (QGraphicsTextItem *textItem = dynamic_cast<QGraphicsTextItem *>(item)){
                if (flagLetter){
                    emit signalLetter();
                    break;
                }
            }
        }
    }
    QGraphicsView::mousePressEvent(event);
}

void CustomGraphicsView::createTextItem(const QString& text, const QPointF& position){
    auto* textItem = scene->addText(text);
    textItem->setDefaultTextColor(Qt::red);

    QFont font = textItem->font();
    font.setPointSize(sizeText);
    textItem->setFont(font);
    textItem->setPos(position - QPointF(textItem->boundingRect().width() / 2, textItem->boundingRect().height() / 2));
    textItem->setZValue(2);
    group2->addToGroup(textItem);
}

void CustomGraphicsView::createWay(){
    flagWay = false;
    dfsThread->start();
    bfsThread->start();
    while(!dfsThread->wait(0) && !bfsThread->wait(0)){
    }

    mutexWay.lock();
    if (flagWay){
        mutexWay.unlock();
        QPen pen(color, 25);
        int offsetW = cellWidth/2;
        int offsetH = cellWidth/2;
        QPainterPath path;
        path.moveTo(pathWay[0].x() * cellWidth - offsetW, pathWay[0].y() * cellHeight - offsetH);
        for (size_t i = 1; i < pathWay.size(); i++) {
            path.lineTo(pathWay[i].x() * cellWidth - offsetW, pathWay[i].y() * cellHeight - offsetH);
        }
        QGraphicsPathItem *pathItem = new QGraphicsPathItem(path);
        pathItem->setPen(pen);
        group2->addToGroup(pathItem);
    } else {
        mutexWay.unlock();
    }
}


//QObject::connect(rectItem, &CustomRectItem::signalTimer, [this](QPointF pos){
//    if (flagLetter && pos != APos){
//        for (QGraphicsItem* item : group1->childItems()) {
//            delete item;
//        }
//        std::set<QPointF> visitedSet;
//        std::vector<QPointF> pathDFS;
//        if (gr->DFS(QPointF((APos.x())/cellWidth + 0.5, APos.y()/cellHeight + 0.5), QPointF(pos.x()/cellWidth + 0.5, pos.y()/cellHeight + 0.5), visitedSet, pathDFS)){
//            QPen pen(Qt::green, 25);
//            int offsetW = cellWidth/2;
//            int offsetH = cellWidth/2;
//            QPainterPath path;
//            path.moveTo(pathDFS[0].x() * cellWidth - offsetW, pathDFS[0].y() * cellHeight - offsetH);
//            for (size_t i = 1; i < pathDFS.size(); i++) {
//                path.lineTo(pathDFS[i].x() * cellWidth - offsetW, pathDFS[i].y() * cellHeight - offsetH);
//            }
//            QGraphicsPathItem *pathItem = new QGraphicsPathItem(path);
//            pathItem->setPen(pen);
//            group1->addToGroup(pathItem);
//        }
//    }
//});
