#include <QtGui>
#include "mainwindow.h"
#include "clicablerenderfactory.h"
//#include "typicalrenderfactory.h"

#include "fileerror.h"
#include "cellularloader.h"
#include "cellularsaver.h"
#include "cellularreseter.h"
#include "cellularclearer.h"

MainWindow::MainWindow() {
    QWidget *widget = new QWidget;
    setCentralWidget(widget);

    int cellular_height = 11;

    _factory = new ClicableRenderFactory(16, 12, cellular_height);
//    _factory = new TypicalRenderFactory(12, 8, cellular_height);
    _render_area = _factory->makeRenderArea(this, 20);

    int area3d_size = _render_area->height();
    _render_area_3d = _factory->makeRenderArea3D(this, area3d_size);

#ifdef CLICABLERENDERFACTORY_H
    connect(_render_area, SIGNAL(cellStateChanged()), _render_area_3d, SLOT(repaint()));
    connect(_render_area, SIGNAL(showInfo()), _render_area_3d, SLOT(showInfo()));
    connect(_render_area, SIGNAL(hideInfo()), _render_area_3d, SLOT(hideInfo()));
#endif

    _slider = new ZSlider(this, cellular_height - 1);
    connect(_slider, SIGNAL(valueChanged(int)), this, SLOT(moveZ(int)));

    QGridLayout *render_layout = new QGridLayout;
    render_layout->addWidget(_render_area, 0, 0);
    render_layout->addWidget(_slider, 0, 1);
    render_layout->addWidget(_render_area_3d, 0, 2);
    _render_group = new QGroupBox(this);
    _render_group->setLayout(render_layout);

    _form_dimer_button = new Button(tr("Build dimer rows"), this);
    connect(_form_dimer_button, SIGNAL(clicked()), this, SLOT(formDimers()));

    _next_button = new Button(tr("Next"), this);
    connect(_next_button, SIGNAL(clicked()), this, SLOT(next()));

    _reset_camera_button = new Button(tr("Reset camera"), this);
    connect(_reset_camera_button, SIGNAL(clicked()), _render_area_3d, SLOT(resetCamera()));

    QGridLayout *buttons_layout = new QGridLayout;
    buttons_layout->addWidget(_form_dimer_button, 0, 0, Qt::AlignCenter);
    buttons_layout->addWidget(_next_button, 0, 1, Qt::AlignCenter);
    buttons_layout->addWidget(_reset_camera_button, 0, 2, Qt::AlignCenter);
    _buttons_group = new QGroupBox(this);
    _buttons_group->setLayout(buttons_layout);

    QVBoxLayout *main_layout = new QVBoxLayout;
    main_layout->addWidget(_render_group);
    main_layout->addWidget(_buttons_group);
    widget->setLayout(main_layout);

    moveWindowToCenter();
    resize(100, 100); // чтобы уменьшилось до минимального размера

    // достаточно создать экземпляр
    _main_menu = new MainMenu(this);

    resetCellular();
}

MainWindow::~MainWindow() {
    delete _reset_camera_button;
    delete _form_dimer_button;
    delete _buttons_group;

    delete _render_area_3d;
    delete _render_area;
    delete _factory;

    delete _render_group;

    delete _main_menu;
}

void MainWindow::openFile() {
    QFileDialog::Options options;
    QString selected_filter;
    QString file_name = QFileDialog::getOpenFileName(this,
                                                     tr("Open cellular data file"),
                                                     tr("~/"),
                                                     tr("Cellular Data Files (*.cdf);;All Files (*)"),
                                                     &selected_filter,
                                                     options);
    if (file_name.isEmpty()) return;
    try {
        CellularLoader(_factory->cellularInstance(), file_name.toStdString()).load();
    } catch (const FileError &error) {
        // выводим в строку состояния
        qDebug() << error.message();
    }

//    updateRenderAreas(); // видимо происходит автоматически
}

void MainWindow::saveFile() {
    QFileDialog::Options options;
    QString selected_filter;
    QString file_name = QFileDialog::getSaveFileName(this,
                                                     tr("Save cellular data file"),
                                                     tr("~/"),
                                                     tr("Cellular Data Files (*.cdf);;All Files (*)"),
                                                     &selected_filter,
                                                     options);
    if (file_name.isEmpty()) return;
    try {
        CellularSaver(_factory->cellularInstance(), file_name.toStdString()).save();
    } catch (const FileError &error) {
        // выводим в строку состояния
        qDebug() << error.message();
    }
}

void MainWindow::resetCellular() {
    CellularReseter(_factory->cellularInstance()).reset();
    resetSlider(1);
}

void MainWindow::clearCellular() {
    CellularClearer(_factory->cellularInstance()).clear();
    resetSlider(0);
}

void MainWindow::updateRenderAreas() {
    _render_area->update();
    _render_area_3d->repaint();
}

void MainWindow::formDimers() {
    _factory->cellularInstance()->buildDimers();
    updateRenderAreas();
}

void MainWindow::next() {
    _factory->cellularInstance()->next();
    updateRenderAreas();
}

void MainWindow::moveZ(int z) {
    _render_area->moveZ(z);
    _render_area_3d->moveZ(z);
    updateRenderAreas();
}

void MainWindow::resetSlider(int new_value) {
    if (_slider->value() == new_value) updateRenderAreas();
    else _slider->setValue(new_value);
}

void MainWindow::moveWindowToCenter() {
    QRect frect = frameGeometry();
    frect.moveCenter(QDesktopWidget().availableGeometry().center());
    move(frect.topLeft());
}
