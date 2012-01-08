#include "complexcell.h"
#include "renderarea.h"

ComplexCell::ComplexCell() : Cell(6) {
    _prect = SingleRect::instance(0, 0, RenderArea::SIMPLE_CELL_SIDE_LENGTH, 2 * RenderArea::SIMPLE_CELL_SIDE_LENGTH);
    _pbrush = SingleColorTool<QBrush>::instance(Qt::transparent);
    _ppen = SingleColorTool<QPen>::instance(Qt::black);
}

void ComplexCell::initNestedNeighbours() {
    first()->setNeighbour(0, neighbour(1)->last());
    first()->setNeighbour(1, neighbour(2)->first());
    first()->setNeighbour(2, neighbour(2)->last());
    first()->setNeighbour(3, neighbour(4)->first());
    first()->setNeighbour(4, last());
    first()->setNeighbour(5, neighbour(3)->first());
    first()->setNeighbour(6, neighbour(0)->last());
    first()->setNeighbour(7, neighbour(0)->first());

    last()->setNeighbour(0, first());
    last()->setNeighbour(1, neighbour(2)->last());
    last()->setNeighbour(2, neighbour(4)->first());
    last()->setNeighbour(3, neighbour(4)->last());
    last()->setNeighbour(4, neighbour(5)->first());
    last()->setNeighbour(5, neighbour(3)->last());
    last()->setNeighbour(6, neighbour(3)->first());
    last()->setNeighbour(7, neighbour(0)->last());
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
        first()->invertState();
    } else {
        last()->invertState();
    }
}

void ComplexCell::resetDimers() {
    for (int i = 0; i < NUMBER_OF_SIMPLE_CELLS; ++i) {
        _cells[i].resetDimer();
    }
}
