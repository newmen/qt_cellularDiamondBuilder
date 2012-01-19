#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QtGui>
#include "cellular.h"
#include "cellspainter.h"

class RenderArea : public QWidget
{
    Q_OBJECT
public:
    RenderArea(QWidget *parent, Cellular *cellular, int z, int one_side_length);
//    ~RenderArea();

    QSize minimumSizeHint() const;
    void paintEvent(QPaintEvent *);

    int oneSideLength() const { return _one_side_length; }
    int topLayerXSeek() const { return (int)((1.5 + _cellular->numX()) * _one_side_length); }
    int topLayerYSeek() const { return (int)(0.5 * _one_side_length); }

signals:

public slots:
    void moveZ(int z);

protected:
    void drawCellular(QPainter *qpainter, CellsPainter *cells_painter);
    Cellular *cellular() { return _cellular; }
    int currZ() const { return _curr_z; }

private:
    Cellular *_cellular;
    int _curr_z;
    const int _one_side_length;
};

#endif // RENDERAREA_H
