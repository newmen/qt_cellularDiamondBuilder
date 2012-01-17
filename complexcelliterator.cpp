#include "complexcelliterator.h"

template<class SimpleCellType>
void ComplexCellIterator<SimpleCellType>::next() {
    if (++_x < 2) return;
    _x = 0;
    ++_y;
}

template<class SimpleCellType>
bool ComplexCellIterator<SimpleCellType>::isDone() const {
    return _y >= 2;
}

template<class SimpleCellType>
SimpleCellType *ComplexCellIterator<SimpleCellType>::current() const {
    if (isDone()) throw IteratorOutOfBounds();
    return _complex_cell->cell(_x, _y);
}
