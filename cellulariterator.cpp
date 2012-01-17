#include "cellulariterator.h"
#include "cellular.h"

//CellularIterator::CellularIterator(Cellular *cellular) : _cellular(cellular), _x(0), _y(0) {}

void CellularIterator::next() {
    if (++_x < _cellular->numX()) return;
    _x = 0;
    ++_y;
}

bool CellularIterator::isDone() const {
    return _y >= _cellular->numY();
}

ComplexCell *CellularIterator::current() const {
    if (isDone()) throw IteratorOutOfBounds();
    return _cellular->cell(_x, _y);
}
