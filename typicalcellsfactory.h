#ifndef TYPICALCELLSFACTORY_H
#define TYPICALCELLSFACTORY_H

#include "cellsfactory.h"
#include "cellular.h"
#include "complexcell.h"
#include "simplecell.h"

class TypicalCellsFactory : public virtual CellsFactory
{
public:
    ComplexCell *makeComplexCell(int state, int x, int y, int z) const {
        return new ComplexCell(this, state, x, y, z);
    }

    SimpleCell *makeSimpleCell(int state, int x, int y) const {
        return new SimpleCell(state, x, y);
    }
};

#endif // TYPICALCELLSFACTORY_H
