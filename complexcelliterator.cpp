#include "complexcelliterator.h"

void ComplexCellIterator::next() {
    if (++_x < 2) return;
    _x = 0;
    ++_y;
}

bool ComplexCellIterator::isDone() const {
    return _y >= 2;
}

SimpleCell *ComplexCellIterator::current() const {
    if (isDone()) throw IteratorOutOfBounds();
    return _complex_cell->cell(_x, _y);
}
