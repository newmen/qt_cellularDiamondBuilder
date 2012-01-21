#ifndef CLICABLECELLSFACTORY_H
#define CLICABLECELLSFACTORY_H

#include "cellsfactory.h"
#include "clicablecomplexcell.h"
#include "clicablesimplecell.h"

class ClicableCellsFactory : public virtual CellsFactory
{
public:
    ComplexCell *makeComplexCell(int state, int x, int y, int z) const {
        return new ClicableComplexCell(this, state, x, y, z);
    }

    SimpleCell *makeSimpleCell(int state, int x, int y) const {
        return new ClicableSimpleCell(state, x, y);
    }
};

#endif // CLICABLECELLSFACTORY_H
