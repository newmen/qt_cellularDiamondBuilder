#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mainmenu.h"
#include "button.h"
#include "zslider.h"
#include "renderarea.h"
#include "renderarea3d.h"
#include "renderfactory.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow();
    ~MainWindow();

public slots:
    void openFile();
    void saveFile();
    void resetCellular();
    void clearCellular();

private slots:
    void updateRenderAreas();
    void formDimers();
    void next();
    void moveZ(int z);

private:
    MainWindow(const MainWindow &);
    MainWindow &operator= (const MainWindow &);

    void moveWindowToCenter();

    MainMenu *_main_menu;

    QGroupBox *_render_group;

    RenderFactory *_factory;
    RenderArea *_render_area;
    RenderArea3D *_render_area_3d;

    ZSlider *_slider;

    QGroupBox *_buttons_group;
    Button *_form_dimer_button;
    Button *_next_button;
    Button *_reset_camera_button;
};

#endif // MAINWINDOW_H
