#include "cellular.h"
#include "cellulariterator.h"
#include "dimersbuilder.h"

template<class ComplexCellType>
Cellular<ComplexCellType>::Cellular(int num_x, int num_y) : _num_x(num_x), _num_y(num_y) {
    _cells = new ComplexCellType**[_num_y];
    for (int y = 0; y < _num_y; ++y) {
        _cells[y] = new ComplexCellType*[_num_x];
        for (int x = 0; x < _num_x; ++x) {
            _cells[y][x] = new ComplexCellType(x, y);
        }
    }

    initNeighbours();
}

template<class ComplexCellType>
Cellular<ComplexCellType>::~Cellular() {
    for (int y = 0; y < _num_y; ++y) {
        for (int x = 0; x < _num_x; ++x) {
            delete [] _cells[y][x];
        }
        delete [] _cells[y];
    }
    delete [] _cells;
}

template<class ComplexCellType>
void Cellular<ComplexCellType>::next() {
//    for (CellularIterator<ComplexCellType> p(this); !p.isDone(); p.next()) {
//        p.current()->resolvNextState();
//    }

//    for (CellularIterator<ComplexCellType> p(this); !p.isDone(); p.next()) {
//        p.current()->next();
//    }

    buildDimers();
}

template<class ComplexCellType>
void Cellular<ComplexCellType>::store(CellVisitor *visitor) {
    for (CellularIterator<ComplexCellType> p(this); !p.isDone(); p.next()) {
        p.current()->store(visitor);
    }
}

template<class ComplexCellType>
void Cellular<ComplexCellType>::initNeighbours() {
    int nx, ny;
    for (CellularIterator<ComplexCellType> p(this); !p.isDone(); p.next()) {
        int neighbour_index = 0;

        for (int iy = -1; iy < 2; ++iy) {
            for (int ix = -2; ix < 3; ++ix) {
                if (iy == 0 && ix == 0) continue;
                if (iy == 1 && ix != 0) continue;
                if (iy != 0 && (ix == -2 || ix == 2)) continue;

                nx = p.x() + ix;
                if (nx < 0) nx += _num_x;
                else if (nx >= _num_x) nx -= _num_x;

                ny = p.y() + iy;
                if (p.x() % 2 != 0 && (ix == -1 || ix == 1)) ++ny;
                if (ny < 0) ny = _num_y - 1;
                else if (ny >= _num_y) ny = 0;

                p.current()->setNeighbour(neighbour_index++, &_cells[ny][nx]);
            }
        }
    }

    for (CellularIterator<ComplexCellType> p(this); !p.isDone(); p.next()) {
        p.current()->initNestedNeighbours();
    }
}

template<class ComplexCellType>
void Cellular<ComplexCellType>::buildDimers() {
    for (CellularIterator<ComplexCellType> p(this); !p.isDone(); p.next()) {
        p.current()->resetDimers();
    }

    DimersBuilder<typename ComplexCellType::InnerCellType> dr_builder;
    typename ComplexCellType::InnerCellType *first, *second;

    for (int part = 0; part < 2; ++part) {
        if (part == 0) {
            dr_builder.reset(2 * _num_y - 1, _num_x - 1);
        } else {
            dr_builder.reset(_num_x - 1, 2 * _num_y - 1);
        }

        for (CellularIterator<ComplexCellType> p(this); !p.isDone(); p.next()) {
            for (int i = 0; i < 2; ++i) {
                if (p.x() % 2 == 0) {
                    second = (i == 0) ? p.current()->cell(0, part)
                                      : p.current()->cell(1, part);
                } else {
                    second = p.current()->cell(0, part);
                    if (i == 0) second = second->front();
                }
                first = second->front();

                if (!first->canBeDimer() || !second->canBeDimer()) continue;

                if (part == 0) {
                    dr_builder.addDimer(2 * p.y() + i, p.x(), first, second);
                } else {
                    dr_builder.addDimer((int)(0.5 * p.x()) * 2 + i, 2 * p.y() + (p.x() % 2), first, second);
                }
            }
        }

        for (typename DimersBuilder<typename ComplexCellType::InnerCellType>::DimerRows::iterator dr = dr_builder.formedRows()->begin();
             dr != dr_builder.formedRows()->end(); ++dr)
        {
            (*dr)->apply();
        }
    }
}
