#include <QtGui>
#include "mainwindow.h"
#include "clicablerenderfactory.h"
//#include "typicalrenderfactory.h"

MainWindow::MainWindow() {
    _factory = new ClicableRenderFactory(16, 10);
//    _factory = new TypicalRenderFactory(16, 10);
    _renderArea = _factory->makeRenderArea(this, 26);
    _nextButton = new Button(tr("Next"), this);

    connect(_nextButton, SIGNAL(clicked()), _renderArea, SLOT(next()));

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(_renderArea);
    mainLayout->addWidget(_nextButton, 0, Qt::AlignCenter);

    moveWindowToCenter();
}

MainWindow::~MainWindow() {
    delete _nextButton;
    delete _renderArea;
    delete _factory;
}

void MainWindow::moveWindowToCenter() {
    QRect frect = frameGeometry();
    frect.moveCenter(QDesktopWidget().availableGeometry().center());
    move(frect.topLeft());
}
