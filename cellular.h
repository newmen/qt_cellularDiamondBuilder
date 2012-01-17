#ifndef CELLULAR_H
#define CELLULAR_H

#include "cellulari.h"
#include "complexcell.h"

template<class ComplexCellType>
class Cellular : public CellularI
{
public:
    Cellular(int num_x, int num_y);
    ~Cellular();

    void next();
    void store(CellVisitor *visitor);

    int numX() const { return _num_x; }
    int numY() const { return _num_y; }

    // для итератора
    ComplexCellType *cell(int x, int y) { return _cells[y][x]; }

private:
    void initNeighbours();
    void buildDimers();

    const int _num_x, _num_y;
    ComplexCellType ***_cells;
};

#endif // CELLULAR_H
