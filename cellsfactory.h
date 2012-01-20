#ifndef CELLSFACTORY_H
#define CELLSFACTORY_H

#include "singlecellularfactory.h"
#include "common.h"

class ComplexCell;
class SimpleCell;

class CellsFactory : public virtual SingleCellularFactory
{
public:
    ~CellsFactory();

    Cellular *cellularInstance();

    virtual ComplexCell *makeComplexCell(int state, int x, int y, int z) const = 0;
    virtual SimpleCell *makeSimpleCell(int state, int x, int y) const = 0;

protected:
    CellsFactory(int cellular_num_x, int cellular_num_y, int cellular_num_z)
        : _single_cellular(0), _cellular_dims(cellular_num_x, cellular_num_y, cellular_num_z) {}

private:
    Cellular *_single_cellular;
    dim3 _cellular_dims;
};

#endif // CELLSFACTORY_H
