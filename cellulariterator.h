#ifndef CELLULARITERATOR_H
#define CELLULARITERATOR_H

#include "complexcell.h"

class Cellular;

class CellularIterator
{
public:
    explicit CellularIterator(Cellular *cellular) : _cellular(cellular) {}

    void next();
    bool isDone() const;
    ComplexCell *current() const;

    int x() const { return _pos.x; }
    int y() const { return _pos.y; }
    int z() const { return _pos.z; }

private:
    Cellular *_cellular;
    int3 _pos;
};

#endif // CELLULARITERATOR_H
