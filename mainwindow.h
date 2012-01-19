#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "button.h"
#include "renderarea.h"
#include "renderfactory.h"

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow();
    ~MainWindow();

private slots:
    void next();

private:
    void moveWindowToCenter();

    QGroupBox *_render_group;

    RenderFactory *_factory;
    RenderArea *_render_area;
    QSlider *_slider;
    Button *_next_button;
};

#endif // MAINWINDOW_H
