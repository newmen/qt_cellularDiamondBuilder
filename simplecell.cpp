#include "simplecell.h"

SimpleCell::SimpleCell(int x, int y) : _x(x), _y(y), _state(0), _next_state(0), _dimer(NONE) {//_hc(0) {
}

//SimpleCell::~SimpleCell() {
//    Cell::~Cell();
//    if (_hc) delete _hc;
//}

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
