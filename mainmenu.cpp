#include "mainmenu.h"
#include <QtGui>

MainMenu::MainMenu(QMainWindow *parent) : QWidget(parent) {
    buildFileMenu(parent);
    buildCellularMenu(parent);
}

MainMenu::~MainMenu() {
    delete _open;
    delete _save;
    delete _exit;

    delete _reset;
    delete _clear;
}

void MainMenu::buildFileMenu(QMainWindow *parent) {
    _open = new QAction(tr("&Open"), this);
    _open->setShortcut(QKeySequence::Open);
    connect(_open, SIGNAL(triggered()), parent, SLOT(openFile()));

    _save = new QAction(tr("&Save"), this);
    _save->setShortcut(QKeySequence::Save);
    connect(_save, SIGNAL(triggered()), parent, SLOT(saveFile()));

    _exit = new QAction(tr("Exit"), this);
    _exit->setShortcut(tr("Alt+W"));
    connect(_exit, SIGNAL(triggered()), parent, SLOT(close()));

    _file = parent->menuBar()->addMenu(tr("&File"));
    _file->addAction(_open);
    _file->addAction(_save);
    _file->addSeparator();
    _file->addAction(_exit);
}

void MainMenu::buildCellularMenu(QMainWindow *parent) {
    _reset = new QAction(tr("Reset"), this);
    _reset->setShortcut(QKeySequence::New);
    connect(_reset, SIGNAL(triggered()), parent, SLOT(resetCellular()));

    _clear = new QAction(tr("Clear"), this);
    connect(_clear, SIGNAL(triggered()), parent, SLOT(clearCellular()));

    _cellular = parent->menuBar()->addMenu(tr("&Cellular"));
    _cellular->addAction(_reset);
    _cellular->addAction(_clear);
}
