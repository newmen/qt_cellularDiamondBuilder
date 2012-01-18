#ifndef CELL_H
#define CELL_H

#include "celli.h"

template<class CellType, int NNeighbours>
class Cell : public virtual CellI
{
public:
//    void setNeighbour(int index, CellI *pcell) { _neighbours[index] = pcell; }
    void setNeighbour(int index, CellType *pcell) { _neighbours[index] = pcell; }

protected:
    Cell() {}

    int neighboursNum() const { return NNeighbours; }
    CellI *neighbour(int index) const { return _neighbours[index]; }
    CellI *changeableNeighbour(int index) { return _neighbours[index]; }
//    CellType *neighbour(int index) const { return dynamic_cast<CellType *>(_neighbours[index]); }
//    CellType *changeableNeighbour(int index) { return dynamic_cast<CellType *>(_neighbours[index]); }
//    CellType *neighbour(int index) const { return _neighbours[index]; }
//    CellType *changeableNeighbour(int index) { return _neighbours[index]; }

    CellType *typedNeighbour(int index) const { return _neighbours[index]; }

private:
//    CellI *_neighbours[NNeighbours];
    CellType *_neighbours[NNeighbours];
};

#endif // CELL_H
