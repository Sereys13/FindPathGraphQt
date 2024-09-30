#include "findway.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<std::vector<QPointF>>("std::vector<QPointF>");
    FindWay w;
    w.show();
    return a.exec();
}
