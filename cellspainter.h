#ifndef CELLSPAINTER_H
#define CELLSPAINTER_H

#include <QtGui>
#include "cellsvisitor.h"

class RenderArea;

class CellsPainter : public CellsVisitor
{
public:
    CellsPainter(RenderArea *render_area, QPainter *qpainter);

    void visitComplexCell(ComplexCell &cell);
    void visitSimpleCell(SimpleCell &cell);

protected:
    RenderArea *renderArea() const { return _render_area; }
    QPainter *painter() { return _painter; }

    void drawComplexCell(ComplexCell &cell, const QColor &color);
    void drawSimpleCell(const SimpleCell &cell, const QColor &color);
    void seek(const SimpleCell &cell, int &x, int &y) const;

private:
    CellsPainter(const CellsPainter &);
    CellsPainter &operator= (const CellsPainter &);

    RenderArea *_render_area;
    QPainter *_painter;

    QRect _complex_cell_rect_top, _complex_cell_rect_bottom;
    QColor _complex_cell_color, _color_info, _color_neighbour_info;
    QPen _complex_cell_border_pen;

    QRect _simple_cell_rect;
    QColor _simple_cell_color0, _simple_cell_color1;
    QPen _simple_cell_border_pen, _simple_cell_dimer_pen;
};

#endif // CELLSPAINTER_H
