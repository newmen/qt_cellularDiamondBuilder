#ifndef CLICABLECELLPAINTER_H
#define CLICABLECELLPAINTER_H

#include "cellpainter.h"
#include "clicablerenderarea.h"

class ClicableCellPainter : public CellPainter
{
public:
    ClicableCellPainter(ClicableRenderArea *render_area, QPainter *painter);

    void visitComplexCell(const ComplexCell &cell);
    void visitSimpleCell(const SimpleCell &cell);

private:
    QColor _complex_cell_color_info, _complex_cell_color_neighbour_info;
    QColor _simple_cell_color_info, _simple_cell_color_neighbour_info;
};

#endif // CLICABLECELLPAINTER_H
