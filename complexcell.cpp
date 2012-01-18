#include "complexcell.h"
#include "complexcelliterator.h"

ComplexCell::ComplexCell(const CellsFactory *cells_factory, int x, int y) : _x(x), _y(y) {
    for (int y = 0; y < 2; ++y) {
        for (int x = 0; x < 2; ++x) {
            _cells[y][x] = cells_factory->createSimpleCell(x, y);
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
    bottomFirstCell()->setNeighbour(1, typedNeighbour(2)->bottomFirstCell());
    bottomFirstCell()->setNeighbour(2, typedNeighbour(2)->bottomSecondCell());
    bottomFirstCell()->setNeighbour(3, typedNeighbour(5)->bottomFirstCell());
    bottomFirstCell()->setNeighbour(4, bottomSecondCell());
    bottomFirstCell()->setNeighbour(5, typedNeighbour(4)->bottomFirstCell());
    bottomFirstCell()->setNeighbour(6, typedNeighbour(0)->bottomSecondCell());
    bottomFirstCell()->setNeighbour(7, typedNeighbour(0)->bottomFirstCell());

    bottomSecondCell()->setNeighbour(0, bottomFirstCell());
    bottomSecondCell()->setNeighbour(1, typedNeighbour(2)->bottomSecondCell());
    bottomSecondCell()->setNeighbour(2, typedNeighbour(5)->bottomFirstCell());
    bottomSecondCell()->setNeighbour(3, typedNeighbour(5)->bottomSecondCell());
    bottomSecondCell()->setNeighbour(4, typedNeighbour(7)->bottomFirstCell());
    bottomSecondCell()->setNeighbour(5, typedNeighbour(4)->bottomSecondCell());
    bottomSecondCell()->setNeighbour(6, typedNeighbour(4)->bottomFirstCell());
    bottomSecondCell()->setNeighbour(7, typedNeighbour(0)->bottomSecondCell());

    topFirstCell()->setNeighbour(0, typedNeighbour(3)->topSecondCell());
    topFirstCell()->setNeighbour(1, typedNeighbour(0)->topFirstCell());
    topFirstCell()->setNeighbour(2, typedNeighbour(0)->topSecondCell());
    topFirstCell()->setNeighbour(3, typedNeighbour(2)->topFirstCell());
    topFirstCell()->setNeighbour(4, topSecondCell());
    topFirstCell()->setNeighbour(5, typedNeighbour(5)->topFirstCell());
    topFirstCell()->setNeighbour(6, typedNeighbour(4)->topSecondCell());
    topFirstCell()->setNeighbour(7, typedNeighbour(4)->topFirstCell());

    topSecondCell()->setNeighbour(0, topFirstCell());
    topSecondCell()->setNeighbour(1, typedNeighbour(0)->topSecondCell());
    topSecondCell()->setNeighbour(2, typedNeighbour(2)->topFirstCell());
    topSecondCell()->setNeighbour(3, typedNeighbour(2)->topSecondCell());
    topSecondCell()->setNeighbour(4, typedNeighbour(6)->topFirstCell());
    topSecondCell()->setNeighbour(5, typedNeighbour(5)->topSecondCell());
    topSecondCell()->setNeighbour(6, typedNeighbour(5)->topFirstCell());
    topSecondCell()->setNeighbour(7, typedNeighbour(4)->topSecondCell());
}
