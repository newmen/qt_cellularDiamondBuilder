#include <QtGui>
#include "mainwindow.h"
#include "typicalcellsfactory.h"

MainWindow::MainWindow() {
    TypicalCellsFactory factory;

    _cellular = new Cellular(&factory, 16, 10);
    _renderArea = new RenderArea(this, _cellular, 26);
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
    delete _cellular;
}

void MainWindow::moveWindowToCenter() {
    QRect frect = frameGeometry();
    frect.moveCenter(QDesktopWidget().availableGeometry().center());
    move(frect.topLeft());
}
