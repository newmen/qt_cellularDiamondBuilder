#ifndef CLICABLECOMPLEXCELL_H
#define CLICABLECOMPLEXCELL_H

#include "clicablecell.h"
#include "complexcell.h"
#include "cellsfactory.h"

class ClicableComplexCell : public ClicableCell, public ComplexCell
{
public:
    ClicableComplexCell(const CellsFactory *cells_factory, int state, int x, int y, int z)
        : ComplexCell(cells_factory, state, x, y, z) {}

private:
    ClicableComplexCell(const ClicableComplexCell &);
    ClicableComplexCell &operator= (const ClicableComplexCell &);
};

#endif // CLICABLECOMPLEXCELL_H
