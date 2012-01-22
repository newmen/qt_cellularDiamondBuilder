#ifndef COMPLEXCELLITERATOR_H
#define COMPLEXCELLITERATOR_H

#include "complexcell.h"
#include "simplecell.h"

class ComplexCellIterator
{
public:
    explicit ComplexCellIterator(ComplexCell *complex_cell) : _complex_cell(complex_cell), _x(0), _y(0) {}

    void next();
    bool isDone() const;
    SimpleCell *current() const;

private:
    ComplexCellIterator(const ComplexCellIterator &);
    ComplexCellIterator &operator= (const ComplexCellIterator &);

    ComplexCell *_complex_cell;
    int _x, _y;
};

#endif // COMPLEXCELLITERATOR_H
