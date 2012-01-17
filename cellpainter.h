#ifndef CELLPAINTER_H
#define CELLPAINTER_H

#include <QtGui>
#include "cellvisitor.h"
#include "renderarea.h"

class CellPainter : public CellVisitor
{
public:
    CellPainter(RenderArea *render_area, QPainter *qpainter);

    void visitComplexCell(const ComplexCell &cell);
    void visitSimpleCell(const SimpleCell &cell);

protected:
    void drawComplexCell(const ComplexCell &cell, const QColor &color);
    void drawSimpleCell(const SimpleCell &cell, const QColor &color);

private:
    RenderArea *_render_area;
    QPainter *_painter;

    QRect _complex_cell_rect_top, _complex_cell_rect_bottom;
    QColor _complex_cell_color, _color_info, _color_neighbour_info;
    QPen _complex_cell_border_pen;

    QRect _simple_cell_rect;
    QColor _simple_cell_color0, _simple_cell_color1;
    QPen _simple_cell_border_pen, _simple_cell_dimer_pen;
};

#endif // CELLPAINTER_H
