#ifndef CLICABLECELLPAINTER_H
#define CLICABLECELLPAINTER_H

#include "cellspainter.h"
#include "clicablerenderarea.h"

class ClicableCellsPainter : public CellsPainter
{
public:
    ClicableCellsPainter(ClicableRenderArea *render_area, QPainter *painter);

    void visitComplexCell(ComplexCell &cell);
    void visitSimpleCell(SimpleCell &cell);

private:
    const QColor *getColor(const CellI &clicable_cell, const QColor &color_info, const QColor &color_neighbour) const;

    QColor _complex_cell_color_info, _complex_cell_color_neighbour_info;
    QColor _simple_cell_color_info, _simple_cell_color_neighbour_info;
};

#endif // CLICABLECELLPAINTER_H
