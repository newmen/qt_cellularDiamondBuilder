#ifndef COMPLEXCELLITERATOR_H
#define COMPLEXCELLITERATOR_H

#include "celliterator.h"
#include "complexcell.h"

template<class SimpleCellType>
class ComplexCellIterator : public CellIterator<SimpleCellType>
{
public:
//    explicit ComplexCellIterator(ComplexCell<SimpleCellType> *complex_cell) : _complex_cell(complex_cell), _x(0), _y(0) {}
    explicit ComplexCellIterator(ComplexCell *complex_cell) : _complex_cell(complex_cell), _x(0), _y(0) {}

    void next();
    bool isDone() const;
    SimpleCellType *current() const;

private:
//    ComplexCell<SimpleCellType> *_complex_cell;
    ComplexCell *_complex_cell;
    int _x, _y;
};

#endif // COMPLEXCELLITERATOR_H
