#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "button.h"
#include "renderarea.h"
#include "cellular.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow();
    ~MainWindow();

private:
    void moveWindowToCenter();

    Cellular *_cellular;
    RenderArea *_renderArea;
    Button *_nextButton;
};

#endif // MAINWINDOW_H
