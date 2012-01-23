#include "cellularreseter.h"
#include "cellsreseter.h"

CellsVisitor *CellularReseter::createVisitor() {
    return new CellsReseter;
}

void CellularReseter::reset() {
    CellsVisitor *cells_reseter = createVisitor();
    cellular()->store(cells_reseter);
    delete cells_reseter;
}
