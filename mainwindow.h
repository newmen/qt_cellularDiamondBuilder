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

private:
    void moveWindowToCenter();

    RenderFactory *_factory;
    RenderArea *_renderArea;
    Button *_nextButton;
};

#endif // MAINWINDOW_H
