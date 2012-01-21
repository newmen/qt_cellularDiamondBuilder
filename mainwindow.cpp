#include <QtGui>
#include "mainwindow.h"
#include "clicablerenderfactory.h"
//#include "typicalrenderfactory.h"

MainWindow::MainWindow() {
    int cellular_height = 5;
    int curr_cellular_z = 1;

    _factory = new ClicableRenderFactory(16, 12, cellular_height);
//    _factory = new TypicalRenderFactory(12, 8, cellular_height);
    _render_area = _factory->makeRenderArea(this, curr_cellular_z, 20);

    int area3d_size = _render_area->height();
    _render_area_3d = _factory->makeRenderArea3D(this, curr_cellular_z, area3d_size);

#ifdef CLICABLERENDERFACTORY_H
    connect(_render_area, SIGNAL(cellStateChanged()), _render_area_3d, SLOT(repaint()));
    connect(_render_area, SIGNAL(showInfo()), _render_area_3d, SLOT(showInfo()));
    connect(_render_area, SIGNAL(hideInfo()), _render_area_3d, SLOT(hideInfo()));
#endif

    _slider = new QSlider(Qt::Vertical, this);
    _slider->setTickPosition(QSlider::TicksBothSides);
    _slider->setTickInterval(2);
    _slider->setSingleStep(1);
    _slider->setMinimum(0);
    _slider->setMaximum(cellular_height - 1);
    _slider->setValue(curr_cellular_z);

    connect(_slider, SIGNAL(valueChanged(int)), this, SLOT(moveZ(int)));

    _form_dimer_button = new Button(tr("Build dimer rows"), this);

    connect(_form_dimer_button, SIGNAL(clicked()), this, SLOT(formDimers()));

    _render_group = new QGroupBox(this);
    QGridLayout *render_layout = new QGridLayout;
    render_layout->addWidget(_render_area, 0, 0);
    render_layout->addWidget(_slider, 0, 1);
    render_layout->addWidget(_render_area_3d, 0, 2);
    _render_group->setLayout(render_layout);

    QVBoxLayout *main_layout = new QVBoxLayout(this);
    main_layout->addWidget(_render_group);
    main_layout->addWidget(_form_dimer_button, 0, Qt::AlignCenter);

    moveWindowToCenter();
}

MainWindow::~MainWindow() {
    delete _form_dimer_button;

    delete _render_area_3d;
    delete _render_area;
    delete _factory;

    delete _render_group;
}

void MainWindow::updateRenderAreas() {
    _render_area->update();
    _render_area_3d->repaint();
}

void MainWindow::formDimers() {
    _factory->cellularInstance()->buildDimers();
    updateRenderAreas();
}

void MainWindow::moveZ(int z) {
    _render_area->moveZ(z);
    _render_area_3d->moveZ(z);
    updateRenderAreas();
}

void MainWindow::moveWindowToCenter() {
    QRect frect = frameGeometry();
    frect.moveCenter(QDesktopWidget().availableGeometry().center());
    move(frect.topLeft());
}
