#include "cellsvisitor.h"
#include "complexcell.h"
#include "simplecell.h"
#include "complexcelliterator.h"

void CellsVisitor::visitSimpleCells(ComplexCell &cell) {
    // TODO: возможно, использование итератора не целесообразно, ввиду его не быстрой работы
    for (ComplexCellIterator p(&cell); !p.isDone(); p.next()) {
        p.current()->store(this);
    }
}
