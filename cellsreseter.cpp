#include "cellsreseter.h"
#include "complexcell.h"
#include "simplecell.h"

void CellsReseter::visitComplexCell(ComplexCell &cell) {
    _is_lower_layer = (cell.z() == 0);
    visitSimpleCells(cell);
}

void CellsReseter::visitSimpleCell(SimpleCell &cell) {
    cell.setState((int)_is_lower_layer);
}
