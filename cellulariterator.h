#ifndef CELLULARITERATOR_H
#define CELLULARITERATOR_H

#include "celliterator.h"
#include "cellular.h"

template<class ComplexCellType>
class CellularIterator : public CellIterator<ComplexCellType>
{
public:
    explicit CellularIterator(Cellular<ComplexCellType> *cellular) : _cellular(cellular), _x(0), _y(0) {}

    void next();
    bool isDone() const;
    ComplexCellType *current() const;

    int x() const { return _x; }
    int y() const { return _y; }

private:
    Cellular<ComplexCellType> *_cellular;
    int _x, _y;
};

#endif // CELLULARITERATOR_H
