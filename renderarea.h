#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QtGui>
#include "cellulari.h"

class RenderArea : public QWidget
{
    Q_OBJECT
public:
    RenderArea(QWidget *parent, CellularI *cellular, int one_side_length);
//    ~RenderArea();

    QSize minimumSizeHint() const;
    void paintEvent(QPaintEvent *);

    int oneSideLength() const { return _one_side_length; }
    int topLayerXSeek() const { return (int)((1.5 + _cellular->numX()) * _one_side_length); }
    int topLayerYSeek() const { return (int)(0.5 * _one_side_length); }

signals:

public slots:
    void next();

protected:
    CellularI *cellular() { return _cellular; }

    template<class CellPainterType> void drawCellular();

private:
    CellularI *_cellular;
    const int _one_side_length;
};

#endif // RENDERAREA_H
