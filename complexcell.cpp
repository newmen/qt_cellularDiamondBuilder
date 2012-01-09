#include "complexcell.h"
#include "renderarea.h"

ComplexCell::ComplexCell() {
    _prect = SingleRect::instance(0, 0, RenderArea::SIMPLE_CELL_SIDE_LENGTH, 2 * RenderArea::SIMPLE_CELL_SIDE_LENGTH);
    _pbrush = SingleColorTool<QBrush>::instance(Qt::transparent);
    _ppen = SingleColorTool<QPen>::instance(Qt::black);
}

void ComplexCell::initNestedNeighbours() {
    first(DOWN)->setNeighbour(0, neighbour(1)->last(DOWN));
    first(DOWN)->setNeighbour(1, neighbour(2)->first(DOWN));
    first(DOWN)->setNeighbour(2, neighbour(2)->last(DOWN));
    first(DOWN)->setNeighbour(3, neighbour(4)->first(DOWN));
    first(DOWN)->setNeighbour(4, last(DOWN));
    first(DOWN)->setNeighbour(5, neighbour(3)->first(DOWN));
    first(DOWN)->setNeighbour(6, neighbour(0)->last(DOWN));
    first(DOWN)->setNeighbour(7, neighbour(0)->first(DOWN));

    last(DOWN)->setNeighbour(0, first(DOWN));
    last(DOWN)->setNeighbour(1, neighbour(2)->last(DOWN));
    last(DOWN)->setNeighbour(2, neighbour(4)->first(DOWN));
    last(DOWN)->setNeighbour(3, neighbour(4)->last(DOWN));
    last(DOWN)->setNeighbour(4, neighbour(5)->first(DOWN));
    last(DOWN)->setNeighbour(5, neighbour(3)->last(DOWN));
    last(DOWN)->setNeighbour(6, neighbour(3)->first(DOWN));
    last(DOWN)->setNeighbour(7, neighbour(0)->last(DOWN));
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
    for (int i = 0; i < NUMBER_OF_SIMPLE_CELLS; ++i) {
        _cells[i].draw(ppainter, x, y + i * RenderArea::SIMPLE_CELL_SIDE_LENGTH);
    }

    ppainter->setPen(*_ppen);
    ppainter->setBrush(*_pbrush);

    ppainter->save();
    ppainter->translate(x, y);
    ppainter->drawRect(*_prect);
    ppainter->restore();
}

void ComplexCell::invertState(int x_seek, int y_seek) {
    if (y_seek < RenderArea::SIMPLE_CELL_SIDE_LENGTH) {
        first(DOWN)->invertState();
    } else {
        last(DOWN)->invertState();
    }
}

void ComplexCell::resetDimers() {
    for (int i = 0; i < NUMBER_OF_SIMPLE_CELLS; ++i) {
        _cells[i].resetDimer();
    }
}
