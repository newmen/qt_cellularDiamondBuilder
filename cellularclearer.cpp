#include "cellularclearer.h"
#include "cellsclearer.h"

CellsVisitor *CellularClearer::createVisitor() {
    return new CellsClearer;
}

void CellularClearer::clear() {
    CellsVisitor *cells_clearer = createVisitor();
    cellular()->store(cells_clearer);
    delete cells_clearer;
}
