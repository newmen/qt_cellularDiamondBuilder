#include "complexcell.h"
#include "renderarea.h"

ComplexCell::ComplexCell() : _info(HIDE) {
    _prect_down = SingleRect::instance(0, 0, RenderArea::SIMPLE_CELL_SIDE_LENGTH, 2 * RenderArea::SIMPLE_CELL_SIDE_LENGTH);
    _prect_up = SingleRect::instance(0, 0, 2 * RenderArea::SIMPLE_CELL_SIDE_LENGTH, RenderArea::SIMPLE_CELL_SIDE_LENGTH);

    Qt::GlobalColor default_global_color = Qt::transparent;
    _pcolor_default = SingleColorTool<QColor>::instance(default_global_color);
    _pcolor_info = SingleColorTool<QColor>::instance(Qt::blue);
    _pcolor_info->setAlphaF(0.35);
    _pcolor_neighbour_info = SingleColorTool<QColor>::instance(Qt::cyan);
    _pcolor_neighbour_info->setAlphaF(0.35);

    _pbrush = SingleColorTool<QBrush>::instance(default_global_color);
    _ppen = SingleColorTool<QPen>::instance(Qt::black);
}

void ComplexCell::initNestedNeighbours() {
    first(DOWN)->setNeighbour(0, neighbour(1)->last(DOWN));
    first(DOWN)->setNeighbour(1, neighbour(2)->first(DOWN));
    first(DOWN)->setNeighbour(2, neighbour(2)->last(DOWN));
    first(DOWN)->setNeighbour(3, neighbour(5)->first(DOWN));
    first(DOWN)->setNeighbour(4, last(DOWN));
    first(DOWN)->setNeighbour(5, neighbour(4)->first(DOWN));
    first(DOWN)->setNeighbour(6, neighbour(0)->last(DOWN));
    first(DOWN)->setNeighbour(7, neighbour(0)->first(DOWN));

    last(DOWN)->setNeighbour(0, first(DOWN));
    last(DOWN)->setNeighbour(1, neighbour(2)->last(DOWN));
    last(DOWN)->setNeighbour(2, neighbour(5)->first(DOWN));
    last(DOWN)->setNeighbour(3, neighbour(5)->last(DOWN));
    last(DOWN)->setNeighbour(4, neighbour(7)->first(DOWN));
    last(DOWN)->setNeighbour(5, neighbour(4)->last(DOWN));
    last(DOWN)->setNeighbour(6, neighbour(4)->first(DOWN));
    last(DOWN)->setNeighbour(7, neighbour(0)->last(DOWN));

    first(UP)->setNeighbour(0, neighbour(3)->last(UP));
    first(UP)->setNeighbour(1, neighbour(0)->first(UP));
    first(UP)->setNeighbour(2, neighbour(0)->last(UP));
    first(UP)->setNeighbour(3, neighbour(2)->first(UP));
    first(UP)->setNeighbour(4, last(UP));
    first(UP)->setNeighbour(5, neighbour(5)->first(UP));
    first(UP)->setNeighbour(6, neighbour(4)->last(UP));
    first(UP)->setNeighbour(7, neighbour(4)->first(UP));

    last(UP)->setNeighbour(0, first(UP));
    last(UP)->setNeighbour(1, neighbour(0)->last(UP));
    last(UP)->setNeighbour(2, neighbour(2)->first(UP));
    last(UP)->setNeighbour(3, neighbour(2)->last(UP));
    last(UP)->setNeighbour(4, neighbour(6)->first(UP));
    last(UP)->setNeighbour(5, neighbour(5)->last(UP));
    last(UP)->setNeighbour(6, neighbour(5)->first(UP));
    last(UP)->setNeighbour(7, neighbour(4)->last(UP));
}

void ComplexCell::resolvNextState() {
    for (int i = 0; i < NUMBER_OF_SIMPLE_CELLS; ++i) {
        _cells[i].resolvNextState();
    }
}

void ComplexCell::next() {
    for (int i = 0; i < NUMBER_OF_SIMPLE_CELLS; ++i) {
        _cells[i].next();
    }
}

void ComplexCell::draw(QPainter* ppainter, int x, int y) const {
    QColor *curr_color;
    switch (_info) {
    case HIDE:
        curr_color = _pcolor_default;
        break;
    case SHOW:
        curr_color = _pcolor_info;
        break;
    case NEIGHBOUR:
        curr_color = _pcolor_neighbour_info;
        break;
    }
    _pbrush->setColor(*curr_color);

    const int half = NUMBER_OF_SIMPLE_CELLS * 0.5;
    for (int i = 0; i < half; ++i) {
        _cells[i].draw(ppainter, x, y + i * RenderArea::SIMPLE_CELL_SIDE_LENGTH);
    }

    ppainter->setPen(*_ppen);
    ppainter->setBrush(*curr_color);

    ppainter->save();
    ppainter->translate(x, y);
    ppainter->drawRect(*_prect_down);
    ppainter->restore();

    int x_seek = x + RenderArea::topLayerXSeek();
    int y_seek = y + RenderArea::topLayerYSeek();
    for (int i = half; i < NUMBER_OF_SIMPLE_CELLS; ++i) {
        _cells[i].draw(ppainter, x_seek + (i - half) * RenderArea::SIMPLE_CELL_SIDE_LENGTH, y_seek);
    }

    ppainter->setPen(*_ppen);
    ppainter->setBrush(*curr_color);

    ppainter->save();
    ppainter->translate(x_seek, y_seek);
    ppainter->drawRect(*_prect_up);
    ppainter->restore();
}

void ComplexCell::invertState(Part part, int x_seek, int y_seek) {
    if (part == DOWN) {
        if (y_seek < RenderArea::SIMPLE_CELL_SIDE_LENGTH) first(DOWN)->invertState();
        else last(DOWN)->invertState();
    } else {
        if (x_seek < RenderArea::SIMPLE_CELL_SIDE_LENGTH) first(UP)->invertState();
        else last(UP)->invertState();
    }
}

void ComplexCell::resetDimers() {
    for (int i = 0; i < NUMBER_OF_SIMPLE_CELLS; ++i) {
        _cells[i].resetDimer();
    }
}

void ComplexCell::showInfo() {
    _info = SHOW;
    for (int i = 0; i < neighboursNum(); ++i) changeableNeighbour(i)->neighbourInfo();
}

void ComplexCell::hideInfo(bool with_neighbours) {
    _info = HIDE;
    if (!with_neighbours) return;
    for (int i = 0; i < neighboursNum(); ++i) changeableNeighbour(i)->hideInfo(false);
}
