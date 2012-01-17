#ifndef CLICABLECOMPLEXCELL_H
#define CLICABLECOMPLEXCELL_H

#include "complexcell.h"
#include "clicablecell.h"
#include "clicablesimplecell.h"

class ClicableComplexCell : public ClicableCell<ComplexCell, 8>, public ComplexCell//<ClicableSimpleCell>
{
};

#endif // CLICABLECOMPLEXCELL_H
