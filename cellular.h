#ifndef CELLULAR_H
#define CELLULAR_H

#include "complexcell.h"

class Cellular
{
public:
    Cellular(const CellsFactory *cells_factory, int num_x, int num_y);
    ~Cellular();

    void next();
    void store(CellsVisitor *visitor);

    int numX() const { return _num_x; }
    int numY() const { return _num_y; }

    // для итератора
    ComplexCell *cell(int x, int y) { return _cells[y][x]; }

private:
    void initNeighbours();
    void buildDimers();

    const int _num_x, _num_y;
    ComplexCell ***_cells;
};

#endif // CELLULAR_H
