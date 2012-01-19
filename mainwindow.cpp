#include <QtGui>
#include "mainwindow.h"
#include "clicablerenderfactory.h"
//#include "typicalrenderfactory.h"

MainWindow::MainWindow() {
    int cellular_height = 3;
    int curr_cellular_z = 1;

    _factory = new ClicableRenderFactory(12, 8, cellular_height);
//    _factory = new TypicalRenderFactory(12, 8, cellular_height);
    _render_area = _factory->makeRenderArea(this, curr_cellular_z, 26);

    _slider = new QSlider(Qt::Vertical, this);
    _slider->setTickPosition(QSlider::TicksBothSides);
    _slider->setTickInterval(2);
    _slider->setSingleStep(1);
    _slider->setMinimum(0);
    _slider->setMaximum(cellular_height - 1);
    _slider->setValue(curr_cellular_z);

    _next_button = new Button(tr("Next"), this);

    connect(_slider, SIGNAL(valueChanged(int)), _render_area, SLOT(moveZ(int)));
    connect(_next_button, SIGNAL(clicked()), this, SLOT(next()));

    _render_group = new QGroupBox(this);
    QGridLayout *render_layout = new QGridLayout;
    render_layout->addWidget(_render_area, 0, 0);
    render_layout->addWidget(_slider, 0, 1);
    _render_group->setLayout(render_layout);

    QVBoxLayout *main_layout = new QVBoxLayout(this);
    main_layout->addWidget(_render_group);
    main_layout->addWidget(_next_button, 0, Qt::AlignCenter);

    moveWindowToCenter();
}

MainWindow::~MainWindow() {
    delete _next_button;
    delete _render_area;
    delete _factory;

    delete _render_group;
}

void MainWindow::next() {
    dynamic_cast<CellsFactory *>(_factory)->cellularInstance()->next();
    _render_area->update();
}

void MainWindow::moveWindowToCenter() {
    QRect frect = frameGeometry();
    frect.moveCenter(QDesktopWidget().availableGeometry().center());
    move(frect.topLeft());
}
