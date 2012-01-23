#include "cellsclearer.h"
#include "complexcell.h"
#include "simplecell.h"

void CellsClearer::visitComplexCell(ComplexCell &cell) {
    visitSimpleCells(cell);
}

void CellsClearer::visitSimpleCell(SimpleCell &cell) {
    cell.setState(0);
}
