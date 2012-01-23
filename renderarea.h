#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QtGui>
#include "renderareai.h"

class RenderArea : public QWidget, public RenderAreaI
{
    Q_OBJECT
public:
    RenderArea(QWidget *parent, Cellular *cellular, int one_side_length);
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
    CellsVisitor *createVisitor();

    QPainter *qpainter() { return _qpainter; }

private:
    RenderArea(const RenderArea &);
    RenderArea &operator= (const RenderArea &);

    QPainter *_qpainter;
    const int _one_side_length;
};

#endif // RENDERAREA_H
