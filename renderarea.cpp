#include "renderarea.h"
#include "dimerrowsplanebuilder.h"

const int RenderArea::COMPLEX_CELLS_NUM_X = 16;
const int RenderArea::COMPLEX_CELLS_NUM_Y = 10;
const int RenderArea::SIMPLE_CELL_SIDE_LENGTH = 26;

RenderArea::RenderArea(QWidget *parent) : QWidget(parent) {
    _cells = new ComplexCell*[COMPLEX_CELLS_NUM_Y];
    for (int i = 0; i < COMPLEX_CELLS_NUM_Y; ++i) {
        _cells[i] = new ComplexCell[COMPLEX_CELLS_NUM_X];
    }

    initNeighbours();
}

RenderArea::~RenderArea() {
    for (int i = 0; i < COMPLEX_CELLS_NUM_Y; ++i) {
        delete [] _cells[i];
    }
    delete [] _cells;
}

QSize RenderArea::minimumSizeHint() const {
    return QSize(COMPLEX_CELLS_NUM_X * SIMPLE_CELL_SIDE_LENGTH, (2 * COMPLEX_CELLS_NUM_Y + 1) * SIMPLE_CELL_SIDE_LENGTH);
}

void RenderArea::mousePressEvent(QMouseEvent* event) {
    int x = event->x() / SIMPLE_CELL_SIDE_LENGTH;
    if (x >= COMPLEX_CELLS_NUM_X) return;
    int inner_seek_x = event->x() % SIMPLE_CELL_SIDE_LENGTH;

    int real_y = event->y();
    if (x % 2 != 0) real_y -= SIMPLE_CELL_SIDE_LENGTH;
    if (real_y < 0) return;

    int y = real_y / (2 * SIMPLE_CELL_SIDE_LENGTH);
    if (y >= COMPLEX_CELLS_NUM_Y) return;
    int inner_seek_y = real_y % (2 * SIMPLE_CELL_SIDE_LENGTH);

    _cells[y][x].invertState(inner_seek_x, inner_seek_y);

    update();
}

void RenderArea::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    for (int y = 0; y < COMPLEX_CELLS_NUM_Y; ++y) {
        for (int x = 0; x < COMPLEX_CELLS_NUM_X; ++x) {
            QPoint p = getCoordinate(x, y);
            _cells[y][x].draw(&painter, p.x(), p.y());
        }
    }

    painter.setRenderHint(QPainter::Antialiasing, false);
}

void RenderArea::next() {
//    for (int y = 0; y < COMPLEX_CELLS_NUM_Y; ++y) {
//        for (int x = 0; x < COMPLEX_CELLS_NUM_X; ++x) {
//            _cells[y][x].resolvNextState();
//        }
//    }

//    for (int y = 0; y < COMPLEX_CELLS_NUM_Y; ++y) {
//        for (int x = 0; x < COMPLEX_CELLS_NUM_X; ++x) {
//            _cells[y][x].next();
//        }
//    }

    buildDimers();
    update();
}

void RenderArea::initNeighbours() {
    int nx, ny;
    for (int y = 0; y < COMPLEX_CELLS_NUM_Y; ++y) {
        for (int x = 0; x < COMPLEX_CELLS_NUM_X; ++x) {
            int neighbour_index = 0;

            for (int iy = -1; iy < 2; ++iy) {
                for (int ix = -1; ix < 2; ++ix) {
                    if (iy == 0 && ix == 0) continue;
                    if (iy == 1 && ix != 0) continue;

                    nx = x + ix;
                    if (nx < 0) nx = COMPLEX_CELLS_NUM_X - 1;
                    else if (nx >= COMPLEX_CELLS_NUM_X) nx = 0;

                    ny = y + iy;
                    if (x % 2 != 0 && ix != 0) ++ny;
                    if (ny < 0) ny = COMPLEX_CELLS_NUM_Y - 1;
                    else if (ny >= COMPLEX_CELLS_NUM_Y) ny = 0;

                    _cells[y][x].setNeighbour(neighbour_index++, &_cells[ny][nx]);
                }
            }
        }
    }

    for (int y = 0; y < COMPLEX_CELLS_NUM_Y; ++y) {
        for (int x = 0; x < COMPLEX_CELLS_NUM_X; ++x) {
            _cells[y][x].initNestedNeighbours();
        }
    }
}

void RenderArea::buildDimers() {
    for (int y = 0; y < COMPLEX_CELLS_NUM_Y; ++y) {
        for (int x = 0; x < COMPLEX_CELLS_NUM_X; ++x) {
            _cells[y][x].resetDimers();
        }
    }

    DimerRowsPlaneBuilder dr_builder(2 * COMPLEX_CELLS_NUM_Y - 1, COMPLEX_CELLS_NUM_X - 1);

    SimpleCell *first, *second;
    for (int y = 0; y < COMPLEX_CELLS_NUM_Y; ++y) {
        for (int x = 0; x < COMPLEX_CELLS_NUM_X; ++x) {
            for (int i = 0; i < 2; ++i) {
                if (x % 2 == 0) {
                    second = (i % 2 == 0) ? _cells[y][x].first(ComplexCell::DOWN) : _cells[y][x].last(ComplexCell::DOWN);
                } else {
                    second = _cells[y][x].first(ComplexCell::DOWN);
                    if (i % 2 == 0) second = second->top();
                }
                first = second->top();

                if (!first->canBeDimer() || !second->canBeDimer()) continue;

                dr_builder.addDimer(2 * y + i, x, first, second);
            }
        }
    }

    dr_builder.formRows();
}

QPoint RenderArea::getCoordinate(int ix, int iy) const {
    int y_seek = iy * 2 * SIMPLE_CELL_SIDE_LENGTH;
    if (ix % 2 != 0) y_seek += SIMPLE_CELL_SIDE_LENGTH;
    return QPoint(ix * SIMPLE_CELL_SIDE_LENGTH, y_seek);
}
