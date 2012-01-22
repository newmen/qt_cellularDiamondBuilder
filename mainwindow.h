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

private slots:
    void updateRenderAreas();
    void formDimers();
    void moveZ(int z);

private:
    MainWindow(const MainWindow &);
    MainWindow &operator= (const MainWindow &);

    void moveWindowToCenter();

    QGroupBox *_render_group;

    RenderFactory *_factory;
    RenderArea *_render_area;
    RenderArea3D *_render_area_3d;

    QSlider *_slider;

    QGroupBox *_buttons_group;
    Button *_form_dimer_button;
    Button *_reset_camera_button;
};

#endif // MAINWINDOW_H
