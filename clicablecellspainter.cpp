//#include <QtGui>
#include "clicablecellspainter.h"
#include "clicablecomplexcell.h"
#include "clicablesimplecell.h"

ClicableCellsPainter::ClicableCellsPainter(ClicableRenderArea *render_area, QPainter *qpainter)
    : CellsPainter(render_area, qpainter)
{
    _complex_cell_color_info = QColor(Qt::blue);
    _complex_cell_color_info.setAlphaF(0.65);
    _complex_cell_color_neighbour_info = QColor(Qt::cyan);
    _complex_cell_color_neighbour_info.setAlphaF(0.35);

    _simple_cell_color_info = QColor(Qt::darkRed);
    _simple_cell_color_info.setAlphaF(0.65);
    _simple_cell_color_neighbour_info = QColor(Qt::red);
    _simple_cell_color_neighbour_info.setAlphaF(0.35);
}

void ClicableCellsPainter::visitComplexCell(ComplexCell &cell) {
    const ClicableComplexCell &clicable_cell = static_cast<const ClicableComplexCell&>(cell);

    QColor *pcolor;
    switch (clicable_cell.info()) {
    case ClicableComplexCell::HIDE:
        CellsPainter::visitComplexCell(cell);
        return;
    case ClicableComplexCell::SHOW:
        pcolor = &_complex_cell_color_info;
        break;
    case ClicableComplexCell::NEIGHBOUR:
        pcolor = &_complex_cell_color_neighbour_info;
        break;
    }
    drawComplexCell(cell, *pcolor);
}

void ClicableCellsPainter::visitSimpleCell(SimpleCell &cell) {
    const ClicableSimpleCell &clicable_cell = static_cast<const ClicableSimpleCell&>(cell);

    QColor *pcolor;
    switch (clicable_cell.info()) {
    case ClicableSimpleCell::HIDE:
        CellsPainter::visitSimpleCell(cell);
        return;
    case ClicableSimpleCell::SHOW:
        pcolor = &_simple_cell_color_info;
        break;
    case ClicableSimpleCell::NEIGHBOUR:
        pcolor = &_simple_cell_color_neighbour_info;
        break;
    }
    drawSimpleCell(cell, *pcolor);
}
