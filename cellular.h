#ifndef CELLULAR_H
#define CELLULAR_H

#include "common.h"
#include "complexcell.h"
#include "cellsfactory.h"

class Cellular
{
public:
    Cellular(const CellsFactory *cells_factory, int dim_x, int dim_y, int dim_z);
    ~Cellular();

    void resize(const dim3 &dims);

    void buildDimers();
    void next();

    void store(CellsVisitor *visitor);
    void storeSlice(int z, CellsVisitor *visitor);

    int dimX() const { return _dims.x; }
    int dimY() const { return _dims.y; }
    int dimZ() const { return _dims.z; }

    // для итератора
    ComplexCell *cell(int x, int y, int z) { return _cells[z][y][x]; }

private:
    Cellular(const Cellular &);
    Cellular &operator= (const Cellular &);

    void createCells();
    void destroyCells();

    void initNeighbours();

    const CellsFactory *_cells_factory;
    ComplexCell ****_cells;
    dim3 _dims;
};

#endif // CELLULAR_H
