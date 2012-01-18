#ifndef CLICABLECOMPLEXCELL_H
#define CLICABLECOMPLEXCELL_H

#include "clicablecell.h"
#include "complexcell.h"
#include "cellsfactory.h"

class ClicableComplexCell : public ClicableCell, public ComplexCell
{
public:
    ClicableComplexCell(const CellsFactory *cells_factory, int x, int y) : ComplexCell(cells_factory, x, y) {}
};

#endif // CLICABLECOMPLEXCELL_H
