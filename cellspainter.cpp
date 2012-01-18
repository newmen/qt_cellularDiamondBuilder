#include "cellspainter.h"
#include "renderarea.h"
#include "complexcell.h"
#include "simplecell.h"

CellsPainter::CellsPainter(RenderArea *render_area, QPainter *qpainter) :
    _render_area(render_area), _painter(qpainter)
{
    _complex_cell_rect_top = QRect(0, 0, 2 * _render_area->oneSideLength(), _render_area->oneSideLength());
    _complex_cell_rect_bottom = QRect(0, 0, _render_area->oneSideLength(), 2 * _render_area->oneSideLength());
    _complex_cell_color = QColor(Qt::transparent);
    _complex_cell_border_pen = QPen(Qt::black);

    _simple_cell_rect = QRect(0, 0, _render_area->oneSideLength(), _render_area->oneSideLength());
    _simple_cell_color0 = QColor(Qt::white);
    _simple_cell_color1 = QColor(Qt::darkGreen);
    _simple_cell_border_pen = QPen(Qt::transparent);
    _simple_cell_dimer_pen = QPen(Qt::darkRed);
    _simple_cell_dimer_pen.setWidth(5);
}

void CellsPainter::visitComplexCell(ComplexCell &cell) {
    drawComplexCell(cell, _complex_cell_color);
}

void CellsPainter::visitSimpleCell(SimpleCell &cell) {
    QColor *pcolor = (cell.state() == 0) ? &_simple_cell_color0 : &_simple_cell_color1;
    drawSimpleCell(cell, *pcolor);
}

void CellsPainter::drawComplexCell(ComplexCell &cell, const QColor &color) {
    for (int inner_y = 0; inner_y < 2; ++inner_y) {
        int real_x = cell.x() * _render_area->oneSideLength();
        int real_y = cell.y() * _render_area->oneSideLength() * 2;
        if (cell.x() % 2 != 0) real_y += _render_area->oneSideLength();

        QRect *prect;
        if (inner_y == 0) {
            prect = &_complex_cell_rect_bottom;
        } else {
            prect = &_complex_cell_rect_top;
            real_x += _render_area->topLayerXSeek();
            real_y += _render_area->topLayerYSeek();
        }

        _painter->save();
        _painter->translate(real_x, real_y);
        for (int inner_x = 0; inner_x < 2; ++inner_x) {
            cell.cell(inner_x, inner_y)->store(this);
        }
        _painter->restore();

        _painter->setBrush(color);
        _painter->setPen(_complex_cell_border_pen);

        _painter->save();
        _painter->translate(real_x, real_y);
        _painter->drawRect(*prect);
        _painter->restore();
    }
}

void CellsPainter::drawSimpleCell(SimpleCell &cell, const QColor &color) {
    int seek = cell.x() * _render_area->oneSideLength();
    int real_x = 0, real_y = 0;
    if (cell.y() == 0) real_y += seek;
    else real_x += seek;

    _painter->setBrush(color);
    _painter->setPen(_simple_cell_border_pen);

    _painter->save();
    _painter->translate(real_x, real_y);
    _painter->drawRect(_simple_cell_rect);
    _painter->restore();

    if (cell.dimer() == SimpleCell::NONE) return;

    _painter->setPen(_simple_cell_dimer_pen);

    _painter->save();

    int half = _render_area->oneSideLength() / 2;
    int half_seek = (cell.dimer() == SimpleCell::FRONT) ? -half : half;
    _painter->translate(real_x + half, real_y + half);

    if (cell.y() == 0) _painter->drawLine(0, 0, 0, half_seek);
    else _painter->drawLine(0, 0, half_seek, 0);

    _painter->restore();
}
