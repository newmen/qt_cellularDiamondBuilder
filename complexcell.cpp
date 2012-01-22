#include "complexcell.h"
#include "complexcelliterator.h"

ComplexCell::ComplexCell(const CellsFactory *cells_factory, int state, int x, int y, int z) : _pos(x, y, z) {
    for (int y = 0; y < 2; ++y) {
        for (int x = 0; x < 2; ++x) {
            _cells[y][x] = cells_factory->makeSimpleCell(state, x, y);
        }
    }
}

ComplexCell::~ComplexCell() {
    for (int y = 0; y < 2; ++y) {
        for (int x = 0; x < 2; ++x) {
            delete _cells[y][x];
        }
    }
}

void ComplexCell::resolvNextState() {
    for (ComplexCellIterator p(this); !p.isDone(); p.next()) p.current()->resolvNextState();
}

void ComplexCell::next() {
    for (ComplexCellIterator p(this); !p.isDone(); p.next()) p.current()->next();
}

void ComplexCell::resetDimers() {
    for (ComplexCellIterator p(this); !p.isDone(); p.next()) p.current()->resetDimer();
}

void ComplexCell::initNestedNeighbours() {
    bottomFirstCell()->setNeighbour(0, typedNeighbour(1)->bottomSecondCell());
    bottomFirstCell()->setNeighbour(1, typedNeighbour(2)->bottomSecondCell());
    bottomFirstCell()->setNeighbour(2, bottomSecondCell());
    bottomFirstCell()->setNeighbour(3, typedNeighbour(0)->bottomSecondCell());
    if (typedNeighbour(9) == 0) {
        bottomFirstCell()->setNeighbour(4, 0);
        bottomFirstCell()->setNeighbour(5, 0);
    } else {
        bottomFirstCell()->setNeighbour(4, typedNeighbour(9)->topFirstCell());
        bottomFirstCell()->setNeighbour(5, typedNeighbour(9)->topSecondCell());
    }
    bottomFirstCell()->setNeighbour(6, typedNeighbour(0)->topSecondCell());
    bottomFirstCell()->setNeighbour(7, topFirstCell());

    bottomSecondCell()->setNeighbour(0, bottomFirstCell());
    bottomSecondCell()->setNeighbour(1, typedNeighbour(5)->bottomFirstCell());
    bottomSecondCell()->setNeighbour(2, typedNeighbour(7)->bottomFirstCell());
    bottomSecondCell()->setNeighbour(3, typedNeighbour(4)->bottomFirstCell());
    if (typedNeighbour(8) == 0) {
        bottomSecondCell()->setNeighbour(4, 0);
        bottomSecondCell()->setNeighbour(5, 0);
    } else {
        bottomSecondCell()->setNeighbour(4, typedNeighbour(8)->topSecondCell());
        bottomSecondCell()->setNeighbour(5, typedNeighbour(10)->topFirstCell());
    }
    bottomSecondCell()->setNeighbour(6, topFirstCell());
    bottomSecondCell()->setNeighbour(7, typedNeighbour(4)->topSecondCell());

    topFirstCell()->setNeighbour(0, typedNeighbour(3)->topSecondCell());
    topFirstCell()->setNeighbour(1, typedNeighbour(0)->topSecondCell());
    topFirstCell()->setNeighbour(2, topSecondCell());
    topFirstCell()->setNeighbour(3, typedNeighbour(4)->topSecondCell());
    topFirstCell()->setNeighbour(4, bottomFirstCell());
    topFirstCell()->setNeighbour(5, bottomSecondCell());
    if (typedNeighbour(11) == 0) {
        topFirstCell()->setNeighbour(6, 0);
        topFirstCell()->setNeighbour(7, 0);
    } else {
        topFirstCell()->setNeighbour(6, typedNeighbour(11)->bottomSecondCell());
        topFirstCell()->setNeighbour(7, typedNeighbour(12)->bottomFirstCell());
    }

    topSecondCell()->setNeighbour(0, topFirstCell());
    topSecondCell()->setNeighbour(1, typedNeighbour(2)->topFirstCell());
    topSecondCell()->setNeighbour(2, typedNeighbour(6)->topFirstCell());
    topSecondCell()->setNeighbour(3, typedNeighbour(5)->topFirstCell());
    topSecondCell()->setNeighbour(4, typedNeighbour(2)->bottomSecondCell());
    topSecondCell()->setNeighbour(5, typedNeighbour(5)->bottomFirstCell());
    if (typedNeighbour(12) == 0) {
        topSecondCell()->setNeighbour(6, 0);
        topSecondCell()->setNeighbour(7, 0);
    } else {
        topSecondCell()->setNeighbour(6, typedNeighbour(12)->bottomFirstCell());
        topSecondCell()->setNeighbour(7, typedNeighbour(13)->bottomSecondCell());
    }
}
