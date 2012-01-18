//#include <QtGui>
#include "clicablecellspainter.h"
#include "clicablecomplexcell.h"
#include "clicablesimplecell.h"

ClicableCellsPainter::ClicableCellsPainter(ClicableRenderArea *render_area, QPainter *qpainter)
    : CellsPainter(render_area, qpainter)
{
    _complex_cell_color_info = QColor(Qt::blue);
    _complex_cell_color_info.setAlphaF(0.6);
    _complex_cell_color_neighbour_info = QColor(Qt::cyan);
    _complex_cell_color_neighbour_info.setAlphaF(0.35);

    _simple_cell_color_info = QColor(Qt::darkRed);
    _simple_cell_color_info.setAlphaF(0.5);
    _simple_cell_color_neighbour_info = QColor(Qt::red);
    _simple_cell_color_neighbour_info.setAlphaF(0.45);
}

void ClicableCellsPainter::visitComplexCell(ComplexCell &cell) {
    if (const QColor *pcolor = getColor(cell, _complex_cell_color_info, _complex_cell_color_neighbour_info)) {
        drawComplexCell(cell, *pcolor);
    } else CellsPainter::visitComplexCell(cell);
}

void ClicableCellsPainter::visitSimpleCell(SimpleCell &cell) {
    if (const QColor *pcolor = getColor(cell, _simple_cell_color_info, _simple_cell_color_neighbour_info)) {
        drawSimpleCell(cell, *pcolor);
    } else CellsPainter::visitSimpleCell(cell);
}

const QColor *ClicableCellsPainter::getColor(const CellI &cell, const QColor &color_info, const QColor &color_neighbour) const {
    const ClicableCell &clicable_cell = dynamic_cast<const ClicableCell &>(cell);

    switch (clicable_cell.info()) {
    case ClicableCell::SHOW:
        return &color_info;
    case ClicableCell::NEIGHBOUR:
        return &color_neighbour;
    }
    return 0;
}
