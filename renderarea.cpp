#include "renderarea.h"
#include "dimerrowsplanebuilder.h"

const int RenderArea::COMPLEX_CELLS_NUM_X = 8;//16;
const int RenderArea::COMPLEX_CELLS_NUM_Y = 8;//10;
const int RenderArea::SIMPLE_CELL_SIDE_LENGTH = 26;

int RenderArea::topLayerXSeek() {
    return (int)((1.5 + COMPLEX_CELLS_NUM_X) * SIMPLE_CELL_SIDE_LENGTH);
}

int RenderArea::topLayerYSeek() {
    return (int)(0.5 * SIMPLE_CELL_SIDE_LENGTH);
}

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
    return QSize(topLayerXSeek() + (COMPLEX_CELLS_NUM_X + 1) * SIMPLE_CELL_SIDE_LENGTH,
                 (2 * COMPLEX_CELLS_NUM_Y + 1) * SIMPLE_CELL_SIDE_LENGTH);
}

void RenderArea::mousePressEvent(QMouseEvent *event) {
    ComplexCell::Part part;
    int x, y;
    int inner_seek_x, inner_seek_y;
    if (event->x() < topLayerXSeek()) {
        part = ComplexCell::DOWN;

        x = event->x() / SIMPLE_CELL_SIDE_LENGTH;
        if (x >= COMPLEX_CELLS_NUM_X) return;
        inner_seek_x = event->x() % SIMPLE_CELL_SIDE_LENGTH;

        int real_y = event->y();
        if (x % 2 != 0) real_y -= SIMPLE_CELL_SIDE_LENGTH;
        if (real_y < 0) return;

        y = real_y / (2 * SIMPLE_CELL_SIDE_LENGTH);
        if (y >= COMPLEX_CELLS_NUM_Y) return;
        inner_seek_y = real_y % (2 * SIMPLE_CELL_SIDE_LENGTH);
    } else {
        part = ComplexCell::UP;

        int real_y = event->y() - topLayerYSeek();
        if (real_y < 0) return;
        y = real_y / SIMPLE_CELL_SIDE_LENGTH;
        if (y >= COMPLEX_CELLS_NUM_Y * 2) return;
        inner_seek_y = real_y % SIMPLE_CELL_SIDE_LENGTH;

        int real_x = event->x() - topLayerXSeek();
        if (y % 2 != 0) real_x -= SIMPLE_CELL_SIDE_LENGTH;
        if (real_x < 0) return;

        x = real_x / (2 * SIMPLE_CELL_SIDE_LENGTH);
        if (x >= COMPLEX_CELLS_NUM_X * 0.5) return;
        inner_seek_x = real_x % (2 * SIMPLE_CELL_SIDE_LENGTH);

        x *= 2;
        if (y % 2 != 0) x += 1;
        y *= 0.5;
    }

    if (event->button() != Qt::RightButton) {
        _cells[y][x].invertState(part, inner_seek_x, inner_seek_y);
    } else {
        _cells[y][x].showInfo();
        _curr_right_x_index = x;
        _curr_right_y_index = y;
    }

    update();
}

void RenderArea::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() != Qt::RightButton) return;
    _cells[_curr_right_y_index][_curr_right_x_index].hideInfo();

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
                for (int ix = -2; ix < 3; ++ix) {
                    if (iy == 0 && ix == 0) continue;
                    if (iy == 1 && ix != 0) continue;
                    if (iy != 0 && (ix == -2 || ix == 2)) continue;

                    nx = x + ix;
                    if (nx < 0) nx += COMPLEX_CELLS_NUM_X;
                    else if (nx >= COMPLEX_CELLS_NUM_X) nx -= COMPLEX_CELLS_NUM_X;

                    ny = y + iy;
                    if (x % 2 != 0 && (ix == -1 || ix == 1)) ++ny;
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

    DimerRows formed_rows;
    SimpleCell *first, *second;

    for (int part = 0; part < 2; ++part) {
        DimerRowsPlaneBuilder dr_builder(2 * COMPLEX_CELLS_NUM_Y - 1, COMPLEX_CELLS_NUM_X - 1);

        for (int y = 0; y < COMPLEX_CELLS_NUM_Y; ++y) {
            for (int x = 0; x < COMPLEX_CELLS_NUM_X; ++x) {
                for (int i = 0; i < 2; ++i) {
                    if (x % 2 == 0) {
                        second = (i % 2 == 0) ? _cells[y][x].first((ComplexCell::Part)part) : _cells[y][x].last((ComplexCell::Part)part);
                    } else {
                        second = _cells[y][x].first((ComplexCell::Part)part);
                        if (i % 2 == 0) second = second->top();
                    }
                    first = second->top();

                    if (!first->canBeDimer() || !second->canBeDimer()) continue;

                    if (part == 0) dr_builder.addDimer(2 * y + i, x, first, second);
//                    else dr_builder.addDimer(, , first, second);
                }
            }
        }

        formed_rows.splice(formed_rows.end(), dr_builder.getFormedRows());
    }

    for (DimerRows::iterator dr = formed_rows.begin(); dr != formed_rows.end(); ++dr) {
        (*dr)->apply();
    }
}

QPoint RenderArea::getCoordinate(int ix, int iy) const {
    int y_seek = iy * 2 * SIMPLE_CELL_SIDE_LENGTH;
    if (ix % 2 != 0) y_seek += SIMPLE_CELL_SIDE_LENGTH;
    return QPoint(ix * SIMPLE_CELL_SIDE_LENGTH, y_seek);
}
