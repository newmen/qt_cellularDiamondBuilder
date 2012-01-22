//#include <QtGui>
#include "clicablecellspainter.h"
//#include "clicablecomplexcell.h"
#include "clicablesimplecell.h"

ClicableCellsPainter::ClicableCellsPainter(ClicableRenderArea *render_area, QPainter *qpainter)
    : CellsPainter(render_area, qpainter)
{
    _complex_cell_color_info = QColor(Qt::blue);
    _complex_cell_color_info.setAlphaF(0.5);
    _complex_cell_color_neighbour_info = QColor(Qt::cyan);
    _complex_cell_color_neighbour_info.setAlphaF(0.33);

    _simple_cell_color_info = QColor(Qt::darkRed);
    _simple_cell_color_info.setAlphaF(0.33);
    _simple_cell_color_neighbour_info = QColor(Qt::red);
    _simple_cell_color_neighbour_info.setAlphaF(0.5);

    _cross_pen = QPen(Qt::red);
    _cross_pen.setWidth(0.5);
}

void ClicableCellsPainter::visitComplexCell(ComplexCell &cell) {
    if (const QColor *pcolor = getColor(cell, _complex_cell_color_info, _complex_cell_color_neighbour_info)) {
        drawComplexCell(cell, *pcolor);
    } else CellsPainter::visitComplexCell(cell);
}

void ClicableCellsPainter::visitSimpleCell(SimpleCell &cell) {
    ClicableSimpleCell &clicable_simple_cell = static_cast<ClicableSimpleCell &>(cell);
    if (clicable_simple_cell.bottomIs()) CellsPainter::visitSimpleCell(cell);
    else drawCross(cell);

    if (const QColor *pcolor = getColor(cell, _simple_cell_color_info, _simple_cell_color_neighbour_info)) {
        drawSimpleCell(cell, *pcolor);
    }
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

void ClicableCellsPainter::drawCross(const SimpleCell &cell) {
    int real_x, real_y;
    seek(cell, real_x, real_y);

    painter()->setPen(_cross_pen);

    painter()->save();
    painter()->translate(real_x, real_y);
    painter()->drawLine(0, 0, renderArea()->oneSideLength(), renderArea()->oneSideLength());
    painter()->drawLine(0, renderArea()->oneSideLength(), renderArea()->oneSideLength(), 0);
    painter()->restore();
}
