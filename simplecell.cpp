#include "simplecell.h"
#include "renderarea.h"

SimpleCell::SimpleCell() : _state(0), _next_state(0), _dimer(NONE) {//_hc(0) {
    _prect = SingleRect::instance(0, 0, RenderArea::SIMPLE_CELL_SIDE_LENGTH, RenderArea::SIMPLE_CELL_SIDE_LENGTH);
    _pbrush0 = SingleColorTool<QBrush>::instance(Qt::white);
    _pbrush1 = SingleColorTool<QBrush>::instance(Qt::darkGreen);
    _ppen = SingleColorTool<QPen>::instance(Qt::transparent);
    _pdimer_pen = SingleColorTool<QPen>::instance(Qt::darkRed);
    _pdimer_pen->setWidth(5);
}

//SimpleCell::~SimpleCell() {
//    Cell::~Cell();
//    if (_hc) delete _hc;
//}

void SimpleCell::invertState() {
    _state = 1 - _state;
}

void SimpleCell::resolvNextState() {
    int sum = 0;
    for (int i = 0; i < neighboursNum(); ++i) {
        if (neighbour(i)->_state == 1) ++sum;
    }

    if ((_state == 0 && sum == 3) || (_state == 1 && (sum == 2 || sum == 3))) _next_state = 1;
    else _next_state = 0;
}

void SimpleCell::next() {
    _state = _next_state;
}

void SimpleCell::draw(QPainter* ppainter, int x, int y) const {
    QBrush* pbrush = (_state == 0) ? _pbrush0 : _pbrush1;
//    QBrush* pbrush = (!_hc) ? _pbrush0 : _pbrush1;

    ppainter->setBrush(*pbrush);
    ppainter->setPen(*_ppen);

    ppainter->save();
    ppainter->translate(x, y);
    ppainter->drawRect(*_prect);
    ppainter->restore();

    if (_dimer == NONE) return;

    ppainter->setPen(*_pdimer_pen);

    ppainter->save();
    int half = RenderArea::SIMPLE_CELL_SIDE_LENGTH / 2;
    ppainter->translate(x + half, y + half);
    if (_dimer == DOWN || _dimer == UP) {
        ppainter->drawLine(0, 0, 0, ((_dimer == DOWN) ? half : -half));
    } else {
        ppainter->drawLine(0, 0, ((_dimer == RIGHT) ? half : -half), 0);
    }
    ppainter->restore();
}
