#include "complexcell.h"
#include "complexcelliterator.h"

//template<class SimpleCellType>
//ComplexCell<SimpleCellType>::ComplexCell(int x, int y) : _x(x), _y(y) {
ComplexCell::ComplexCell(int x, int y) : _x(x), _y(y) {
    for (int y = 0; y < 2; ++y) {
        for (int x = 0; x < 2; ++x) {
            _cells[y][x] = new SimpleCellType(x, y);
        }
    }
}

//template<class SimpleCellType>
//ComplexCell<SimpleCellType>::~ComplexCell() {
ComplexCell::~ComplexCell() {
    for (int y = 0; y < 2; ++y) {
        for (int x = 0; x < 2; ++x) {
            delete _cells[y][x];
        }
    }
}

//template<class SimpleCellType>
//void ComplexCell<SimpleCellType>::resolvNextState() {
void ComplexCell::resolvNextState() {
    for (ComplexCellIterator<SimpleCellType> p(this); !p.isDone(); p.next()) p.current()->resolvNextState();
}

//template<class SimpleCellType>
//void ComplexCell<SimpleCellType>::next() {
void ComplexCell::next() {
    for (ComplexCellIterator<SimpleCellType>p(this); !p.isDone(); p.next()) p.current()->next();
}

//template<class SimpleCellType>
//void ComplexCell<SimpleCellType>::resetDimers() {
void ComplexCell::resetDimers() {
    for (ComplexCellIterator<SimpleCellType>p(this); !p.isDone(); p.next()) p.current()->resetDimer();
}

//template<class SimpleCellType>
//void ComplexCell<SimpleCellType>::initNestedNeighbours() {
void ComplexCell::initNestedNeighbours() {
    cell(0, 0)->setNeighbour(0, neighbour(1)->cell(0, 1));
    cell(0, 0)->setNeighbour(1, neighbour(2)->cell(0, 0));
    cell(0, 0)->setNeighbour(2, neighbour(2)->cell(0, 1));
    cell(0, 0)->setNeighbour(3, neighbour(5)->cell(0, 0));
    cell(0, 0)->setNeighbour(4, cell(0, 1));
    cell(0, 0)->setNeighbour(5, neighbour(4)->cell(0, 0));
    cell(0, 0)->setNeighbour(6, neighbour(0)->cell(0, 1));
    cell(0, 0)->setNeighbour(7, neighbour(0)->cell(0, 0));

    cell(0, 1)->setNeighbour(0, cell(0, 0));
    cell(0, 1)->setNeighbour(1, neighbour(2)->cell(0, 1));
    cell(0, 1)->setNeighbour(2, neighbour(5)->cell(0, 0));
    cell(0, 1)->setNeighbour(3, neighbour(5)->cell(0, 1));
    cell(0, 1)->setNeighbour(4, neighbour(7)->cell(0, 0));
    cell(0, 1)->setNeighbour(5, neighbour(4)->cell(0, 1));
    cell(0, 1)->setNeighbour(6, neighbour(4)->cell(0, 0));
    cell(0, 1)->setNeighbour(7, neighbour(0)->cell(0, 1));

    cell(1, 0)->setNeighbour(0, neighbour(3)->cell(1, 1));
    cell(1, 0)->setNeighbour(1, neighbour(0)->cell(1, 0));
    cell(1, 0)->setNeighbour(2, neighbour(0)->cell(1, 1));
    cell(1, 0)->setNeighbour(3, neighbour(2)->cell(1, 0));
    cell(1, 0)->setNeighbour(4, cell(1, 1));
    cell(1, 0)->setNeighbour(5, neighbour(5)->cell(1, 0));
    cell(1, 0)->setNeighbour(6, neighbour(4)->cell(1, 1));
    cell(1, 0)->setNeighbour(7, neighbour(4)->cell(1, 0));

    cell(1, 1)->setNeighbour(0, cell(1, 0));
    cell(1, 1)->setNeighbour(1, neighbour(0)->cell(1, 1));
    cell(1, 1)->setNeighbour(2, neighbour(2)->cell(1, 0));
    cell(1, 1)->setNeighbour(3, neighbour(2)->cell(1, 1));
    cell(1, 1)->setNeighbour(4, neighbour(6)->cell(1, 0));
    cell(1, 1)->setNeighbour(5, neighbour(5)->cell(1, 1));
    cell(1, 1)->setNeighbour(6, neighbour(5)->cell(1, 0));
    cell(1, 1)->setNeighbour(7, neighbour(4)->cell(1, 1));
}
