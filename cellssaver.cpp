#include "cellssaver.h"
#include "complexcell.h"
#include "simplecell.h"

void CellsSaver::visitComplexCell(ComplexCell &cell) {
    if (isEmpty(cell)) return;

    _file << cell.x() << ' ' << cell.y() << ' ' << cell.z() << '\t';
    for (int y = 0; y < 2; ++y) {
        for (int x = 0; x < 2; ++x) {
            cell.cell(x, y)->store(this);
            _file << ' ';
        }
    }
    _file << '\n';
}

void CellsSaver::visitSimpleCell(SimpleCell &cell) {
    _file << cell.state();
}

bool CellsSaver::isEmpty(ComplexCell &cell) {
    bool result = true;
    for (int y = 0; y < 2; ++y) {
        for (int x = 0; x < 2; ++x) {
            if (cell.cell(x, y)->state() == 0) continue;
            result = false;
            break;
        }
    }
    return result;
}
