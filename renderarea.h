#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QtGui>
#include "complexcell.h"

class RenderArea : public QWidget
{
    Q_OBJECT
public:
    explicit RenderArea(QWidget *parent = 0);
    ~RenderArea();

    QSize minimumSizeHint() const;

    void mousePressEvent(QMouseEvent *);
    void paintEvent(QPaintEvent*);

    static const int COMPLEX_CELLS_NUM_X;
    static const int COMPLEX_CELLS_NUM_Y;

    static const int SIMPLE_CELL_SIDE_LENGTH;
signals:

public slots:
    void next();

private:
    void initNeighbours();
    void buildDimers();
    QPoint getCoordinate(int ix, int iy) const;

    ComplexCell **_cells;

};

#endif // RENDERAREA_H
