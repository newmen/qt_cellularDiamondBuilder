#ifndef CELLULARI_H
#define CELLULARI_H

#include "cellvisitor.h"

class CellularI
{
public:
    virtual ~CellularI() {}

    virtual void next() = 0;
    virtual void store(CellVisitor *visitor) = 0;

    virtual int numX() const = 0;
    virtual int numY() const = 0;

protected:
    CellularI() {}
};

#endif // CELLULARI_H
