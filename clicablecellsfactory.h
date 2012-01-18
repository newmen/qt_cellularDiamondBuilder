#ifndef CLICABLECELLSFACTORY_H
#define CLICABLECELLSFACTORY_H

#include "cellsfactory.h"
#include "clicablecomplexcell.h"
#include "clicablesimplecell.h"

class ClicableCellsFactory : public CellsFactory
{
public:
    ClicableCellsFactory(int cellular_num_x, int cellular_num_y) : CellsFactory(cellular_num_x, cellular_num_y) {}

    ComplexCell *makeComplexCell(int x, int y) const {
        return new ClicableComplexCell(this, x, y);
    }

    SimpleCell *makeSimpleCell(int x, int y) const {
        return new ClicableSimpleCell(x, y);
    }
};

#endif // CLICABLECELLSFACTORY_H
