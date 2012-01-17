#ifndef TYPICALCELLSFACTORY_H
#define TYPICALCELLSFACTORY_H

#include "cellsfactory.h"
#include "complexcell.h"
#include "simplecell.h"

class TypicalCellsFactory : public CellsFactory
{
public:
    ComplexCell *createComplexCell(int x, int y) const {
        return new ComplexCell(this, x, y);
    }

    SimpleCell *createSimpleCell(int x, int y) const {
        return new SimpleCell(x, y);
    }
};

#endif // TYPICALCELLSFACTORY_H
