#-------------------------------------------------
#
# Project created by QtCreator 2011-11-28T16:40:56
#
#-------------------------------------------------

QT += core gui opengl xml
#QT += opengl xml

QMAKE_CXXFLAGS += -std=c++0x

TARGET = diamond_2d_area
TEMPLATE = app

LIBS += -lqglviewer-qt4

SOURCES += main.cpp\
        mainwindow.cpp \
    renderarea.cpp \
    simplecell.cpp \
    complexcell.cpp \
    cell.cpp \
    hydrocarbon.cpp \
    button.cpp \
    dimerrow.cpp \
    cellular.cpp \
    cellulariterator.cpp \
    clicablesimplecell.cpp \
    clicablecomplexcell.cpp \
    dimersbuilder.cpp \
    complexcelliterator.cpp \
    clicablerenderarea.cpp \
    clicablecell.cpp \
    cellsfactory.cpp \
    typicalcellsfactory.cpp \
    clicablecellsfactory.cpp \
    cellspainter.cpp \
    cellsvisitor.cpp \
    clicablecellspainter.cpp \
    iteratoroutofbounds.cpp \
    celli.cpp \
    renderfactory.cpp \
    typicalrenderfactory.cpp \
    clicablerenderfactory.cpp \
    renderarea3d.cpp \
    cellspainter3d.cpp \
    renderareai.cpp \
    inforenderarea3d.cpp \
    infocellspainter3d.cpp

HEADERS  += mainwindow.h \
    renderarea.h \
    simplecell.h \
    complexcell.h \
    cell.h \
    hydrocarbon.h \
    button.h \
    dimerrow.h \
    cellular.h \
    cellulariterator.h \
    clicablesimplecell.h \
    clicablecomplexcell.h \
    dimersbuilder.h \
    complexcelliterator.h \
    clicablerenderarea.h \
    clicablecell.h \
    cellsfactory.h \
    typicalcellsfactory.h \
    clicablecellsfactory.h \
    cellspainter.h \
    cellsvisitor.h \
    clicablecellspainter.h \
    iteratoroutofbounds.h \
    celli.h \
    renderfactory.h \
    typicalrenderfactory.h \
    clicablerenderfactory.h \
    common.h \
    renderarea3d.h \
    cellspainter3d.h \
    renderareai.h \
    inforenderarea3d.h \
    infocellspainter3d.h

OTHER_FILES += \
    TODO.txt

