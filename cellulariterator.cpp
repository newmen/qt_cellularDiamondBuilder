#include "cellulariterator.h"
#include "cellular.h"
#include "iteratoroutofbounds.h"

void CellularIterator::next() {
    if (++_pos.x < _cellular->dimX()) return;
    _pos.x = 0;
    if (++_pos.y < _cellular->dimY()) return;
    _pos.y = 0;
    ++_pos.z;
}

bool CellularIterator::isDone() const {
    return _pos.z >= _cellular->dimZ();
}

ComplexCell *CellularIterator::current() const {
    if (isDone()) throw IteratorOutOfBounds();
    return _cellular->cell(_pos.x, _pos.y, _pos.z);
}
