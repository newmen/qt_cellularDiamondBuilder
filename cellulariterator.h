#ifndef CELLULARITERATOR_H
#define CELLULARITERATOR_H

#include "complexcell.h"

class Cellular;

class CellularIterator
{
public:
    explicit CellularIterator(Cellular *cellular) : _cellular(cellular), _x(0), _y(0) {}

    void next();
    bool isDone() const;
    ComplexCell *current() const;

    int x() const { return _x; }
    int y() const { return _y; }

private:
    Cellular *_cellular;
    int _x, _y;
};

#endif // CELLULARITERATOR_H
