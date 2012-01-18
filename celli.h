#ifndef CELLI_H
#define CELLI_H

#include "cellsvisitor.h"

class CellI
{
public:
    virtual ~CellI() {}

    virtual void resolvNextState() = 0;
    virtual void next() = 0;
    virtual void store(CellsVisitor *visitor) = 0;

//    virtual void setNeighbour(int index, CellI* neighbour_cell) = 0;

protected:
    CellI() {}

    virtual int neighboursNum() const = 0;
    virtual CellI *neighbour(int index) const = 0;
    virtual CellI *changeableNeighbour(int index) = 0;
};

#endif // CELLI_H
