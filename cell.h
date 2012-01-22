#ifndef CELL_H
#define CELL_H

#include "celli.h"

template<class CellType, int NNeighbours>
class Cell : public virtual CellI
{
public:
    void setNeighbour(int index, CellType *pcell) { _neighbours[index] = pcell; }

protected:
    Cell() {}

    int neighboursNum() const { return NNeighbours; }
    CellI *neighbour(int index) const { return _neighbours[index]; }
    CellI *changeableNeighbour(int index) { return _neighbours[index]; }

    CellType *typedNeighbour(int index) const { return _neighbours[index]; }

private:
    CellType *_neighbours[NNeighbours];

    Cell(const Cell &);
    Cell &operator= (const Cell &);
};

#endif // CELL_H
