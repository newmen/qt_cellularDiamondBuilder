#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "button.h"
#include "renderarea.h"
#include "cellulari.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow();
    ~MainWindow();

private:
    void moveWindowToCenter();

    CellularI *_cellular;
    RenderArea *_renderArea;
    Button *_nextButton;
};

#endif // MAINWINDOW_H
