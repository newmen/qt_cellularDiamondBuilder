#include <QtGui>
#include "mainwindow.h"

MainWindow::MainWindow() {
    _renderArea = new RenderArea(this);
    _nextButton = new Button(tr("Next"), this);

    connect(_nextButton, SIGNAL(clicked()), _renderArea, SLOT(next()));

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(_renderArea);
    mainLayout->addWidget(_nextButton, 0, Qt::AlignCenter);

    moveWindowToCenter();
}

MainWindow::~MainWindow() {
    delete _renderArea;
    delete _nextButton;
}

void MainWindow::moveWindowToCenter() {
    QRect frect = frameGeometry();
    frect.moveCenter(QDesktopWidget().availableGeometry().center());
    move(frect.topLeft());
}
