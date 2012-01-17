#ifndef CLICABLECELLSFACTORY_H
#define CLICABLECELLSFACTORY_H

#include "cellsfactory.h"
#include "clicablecomplexcell.h"
#include "clicablesimplecell.h"

class ClicableCellsFactory : public CellsFactory
{
public:
    ComplexCell *createComplexCell(int x, int y) const {
        return new ClicableComplexCell(this, x, y);
    }

    SimpleCell *createSimpleCell(int x, int y) const {
        return new ClicableSimpleCell(x, y);
    }
};

#endif // CLICABLECELLSFACTORY_H
