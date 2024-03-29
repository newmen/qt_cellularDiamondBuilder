#include "cellular.h"
#include "cellulariterator.h"
#include "dimersbuilder.h"

Cellular::Cellular(const CellsFactory *cells_factory, int dim_x, int dim_y, int dim_z)
    : _cells_factory(cells_factory), _dims(dim_x, dim_y, dim_z)
{
    createCells();
}

Cellular::~Cellular() {
    destroyCells();
}

void Cellular::resize(const dim3 &dims) {
    destroyCells();
    _dims = dims;
    createCells();
}

void Cellular::buildDimers() {
    for (CellularIterator p(this); !p.isDone(); p.next()) {
        p.current()->resetDimers();
    }

    DimersBuilder dr_builder;
    SimpleCell *first, *second;

    for (int z = 0; z < _dims.z; ++z) {
        for (int part = 0; part < 2; ++part) {
            if (part == 0) {
                dr_builder.reset(2 * _dims.y - 1, _dims.x - 1);
            } else {
                dr_builder.reset(_dims.x - 1, 2 * _dims.y - 1);
            }

            for (int y = 0; y < _dims.y; ++y) {
                for (int x = 0; x < _dims.x; ++x) {
                    for (int i = 0; i < 2; ++i) {
                        if (x % 2 == 0) {
                            second = (i == 0) ? _cells[z][y][x]->cell(0, part)
                                              : _cells[z][y][x]->cell(1, part);
                        } else {
                            second = _cells[z][y][x]->cell(0, part);
                            if (i == 0) second = second->front();
                        }
                        first = second->front();

                        if (!first->canBeDimer() || !second->canBeDimer() || second->topFrontIs()) continue;

                        if (part == 0) {
                            dr_builder.addDimer(2 * y + i, x, first, second);
                        } else {
                            dr_builder.addDimer((int)(0.5 * x) * 2 + i, 2 * y + (x % 2), first, second);
                        }
                    }
                }
            }

            dr_builder.buildRows();
        }
    }

    dr_builder.apply();
}

void Cellular::next() {
    for (CellularIterator p(this); !p.isDone(); p.next()) {
        p.current()->resolvNextState();
    }

    for (CellularIterator p(this); !p.isDone(); p.next()) {
        p.current()->next();
    }

    buildDimers();
}

void Cellular::store(CellsVisitor *visitor) {
    for (CellularIterator p(this); !p.isDone(); p.next()) {
        p.current()->store(visitor);
    }
}

void Cellular::storeSlice(int z, CellsVisitor *visitor) {
    for (int y = 0; y < _dims.y; ++y) {
        for (int x = 0; x < _dims.x; ++x) _cells[z][y][x]->store(visitor);
    }
}

void Cellular::createCells() {
    _cells = new ComplexCell***[_dims.z];
    for (int z = 0; z < _dims.z; ++z) {
        _cells[z] = new ComplexCell**[_dims.y];
        for (int y = 0; y < _dims.y; ++y) {
            _cells[z][y] = new ComplexCell*[_dims.x];
            for (int x = 0; x < _dims.x; ++x) {
                _cells[z][y][x] = _cells_factory->makeComplexCell(0, x, y, z);
            }
        }
    }

    initNeighbours();
}

void Cellular::destroyCells() {
    for (int z = 0; z < _dims.z; ++z) {
        for (int y = 0; y < _dims.y; ++y) {
            for (int x = 0; x < _dims.x; ++x) {
                delete _cells[z][y][x];
            }
            delete [] _cells[z][y];
        }
        delete [] _cells[z];
    }
    delete [] _cells;
}

void Cellular::initNeighbours() {
    int nx, ny, nz;
    CellularIterator p(this);

    auto change_and_check_nx_lambda = [this, &nx, &p](int ix) {
        nx = p.x() + ix;
        if (nx < 0) nx += this->_dims.x;
        else if (nx >= this->_dims.x) nx -= this->_dims.x;
    };

    auto check_ny_lambda = [this, &ny]() {
        if (ny < 0) ny += this->_dims.y;
        else if (ny >= this->_dims.y) ny -= this->_dims.y;
    };

    for (; !p.isDone(); p.next()) {
        int neighbour_index = 0;

        for (int iy = -1; iy < 2; ++iy) {
            for (int ix = -2; ix < 3; ++ix) {
                if (iy == 0 && ix == 0) continue;
                if (iy == 1 && ix != 0) continue;
                if (iy != 0 && (ix == -2 || ix == 2)) continue;

                change_and_check_nx_lambda(ix);

                ny = p.y() + iy;
                if (p.x() % 2 != 0 && (ix == -1 || ix == 1)) ++ny;
                check_ny_lambda();

                p.current()->setNeighbour(neighbour_index++, _cells[p.z()][ny][nx]);
            }
        }

        for (int iz = -1; iz < 2; iz += 2) {
            nz = p.z() + iz;
            for (int ix = -1; ix < 2; ++ix) {
                int curr_neighbour_index = neighbour_index++;

                if (nz < 0 || nz >= _dims.z) {
                    p.current()->setNeighbour(curr_neighbour_index, 0);
                    continue;
                }

                change_and_check_nx_lambda(ix);

                ny = p.y();
                if (iz == -1 && ix != 0 && p.x() % 2 != 0) ++ny;
                else if (iz == 1 && ix != 0 && p.x() % 2 == 0) --ny;
                check_ny_lambda();

                p.current()->setNeighbour(curr_neighbour_index, _cells[nz][ny][nx]);
            }
        }
    }

    for (CellularIterator p(this); !p.isDone(); p.next()) {
        p.current()->initNestedNeighbours();
    }
}
