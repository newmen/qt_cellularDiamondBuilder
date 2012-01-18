#ifndef TYPICALCELLSFACTORY_H
#define TYPICALCELLSFACTORY_H

#include "cellsfactory.h"
#include "cellular.h"
#include "complexcell.h"
#include "simplecell.h"

class TypicalCellsFactory : public CellsFactory
{
public:
    TypicalCellsFactory(int cellular_num_x, int cellular_num_y) : CellsFactory(cellular_num_x, cellular_num_y) {}

    ComplexCell *makeComplexCell(int x, int y) const {
        return new ComplexCell(this, x, y);
    }

    SimpleCell *makeSimpleCell(int x, int y) const {
        return new SimpleCell(x, y);
    }
};

#endif // TYPICALCELLSFACTORY_H
