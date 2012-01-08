#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "renderarea.h"
#include "button.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow();
    ~MainWindow();

private:
    void moveWindowToCenter();

    RenderArea* _renderArea;
    Button* _nextButton;
};

#endif // MAINWINDOW_H
