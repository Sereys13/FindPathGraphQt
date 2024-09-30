QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TARGET = FindPathGraph

SOURCES += \
    src/bfsworker.cpp \
    src/customgraphicsview.cpp \
    src/customintvalidator.cpp \
    src/customrectitem.cpp \
    src/dfsworker.cpp \
    src/graph.cpp \
    src/main.cpp \
    src/findway.cpp

INCLUDEPATH += include

HEADERS += \
    include/bfsworker.h \
    include/customgraphicsview.h \
    include/customintvalidator.h \
    include/customrectitem.h \
    include/dfsworker.h \
    include/findway.h \
    include/graph.h

FORMS += \
    forms/findway.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
