#ifndef CELL_H
#define CELL_H

#include "cellvisitor.h"

template<class CellType, int NNeighbours>
class Cell
{
public:
    virtual void resolvNextState() = 0;
    virtual void next() = 0;
    virtual void store(CellVisitor *visitor) = 0;

    void setNeighbour(int index, CellType* pcell) {
        _neighbours[index] = pcell;
    }

protected:
    Cell() {}

    int neighboursNum() const { return NNeighbours; }
    CellType* neighbour(int index) const { return _neighbours[index]; }
    CellType* changeableNeighbour(int index) { return _neighbours[index]; }

private:
    CellType* _neighbours[NNeighbours];
};

#endif // CELL_H
