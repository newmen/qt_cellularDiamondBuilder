#ifndef CELLULARI_H
#define CELLULARI_H

#include "cellsvisitor.h"

class CellularI
{
public:
    virtual ~CellularI() {}

    virtual void next() = 0;
    virtual void store(CellsVisitor *visitor) = 0;

    virtual int numX() const = 0;
    virtual int numY() const = 0;

protected:
    CellularI() {}
};

#endif // CELLULARI_H
