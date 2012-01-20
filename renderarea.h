#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QtGui>
#include "renderareai.h"
#include "cellspainter.h"

class RenderArea : public QWidget, public RenderAreaI
{
    Q_OBJECT
public:
    RenderArea(QWidget *parent, Cellular *cellular, int z, int one_side_length);
//    ~RenderArea();

    int width() const;
    int height() const;
    QSize minimumSizeHint() const;
    void paintEvent(QPaintEvent *);

    int oneSideLength() const { return _one_side_length; }
    int topLayerXSeek() const { return (int)((1.5 + cellular()->dimX()) * _one_side_length); }
    int topLayerYSeek() const { return (int)(0.5 * _one_side_length); }

signals:

public slots:

protected:
    void drawCellular(QPainter *qpainter, CellsPainter *cells_painter);

private:
    const int _one_side_length;
};

#endif // RENDERAREA_H
