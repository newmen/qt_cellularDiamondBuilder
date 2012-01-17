#include "cellulariterator.h"

//template<class ComplexCellType>
//CellularIterator<ComplexCellType>::CellularIterator(Cellular<ComplexCellType> *cellular) : _cellular(cellular), _x(0), _y(0) {}

template<class ComplexCellType>
void CellularIterator<ComplexCellType>::next() {
    if (++_x < _cellular->numX()) return;
    _x = 0;
    ++_y;
}

template<class ComplexCellType>
bool CellularIterator<ComplexCellType>::isDone() const {
    return _y >= _cellular->numY();
}

template<class ComplexCellType>
ComplexCellType *CellularIterator<ComplexCellType>::current() const {
    if (isDone()) throw IteratorOutOfBounds();
    return _cellular->_cell(_x, _y);
}
