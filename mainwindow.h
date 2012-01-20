#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "button.h"
#include "renderarea.h"
#include "renderarea3d.h"
#include "renderfactory.h"

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow();
    ~MainWindow();

protected:
    void init();

private slots:
    void updateRenderAreas();
    void formDimers();
    void moveZ(int z);

private:
    void moveWindowToCenter();

    QGroupBox *_render_group;

    RenderFactory *_factory;
    RenderArea *_render_area;
    RenderArea3D *_render_area_3d;

    QSlider *_slider;
    Button *_form_dimer_button;
};

#endif // MAINWINDOW_H
