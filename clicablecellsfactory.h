#ifndef CLICABLECELLSFACTORY_H
#define CLICABLECELLSFACTORY_H

#include "cellsfactory.h"
#include "clicablecomplexcell.h"
#include "clicablesimplecell.h"

class ClicableCellsFactory : public CellsFactory
{
public:
    ClicableCellsFactory(int cellular_num_x, int cellular_num_y, int cellular_num_z)
        : CellsFactory(cellular_num_x, cellular_num_y, cellular_num_z) {}

    ComplexCell *makeComplexCell(int state, int x, int y, int z) const {
        return new ClicableComplexCell(this, state, x, y, z);
    }

    SimpleCell *makeSimpleCell(int state, int x, int y) const {
        return new ClicableSimpleCell(state, x, y);
    }
};

#endif // CLICABLECELLSFACTORY_H
