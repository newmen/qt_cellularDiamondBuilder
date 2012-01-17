#include "clicablerenderarea.h"
#include "clicablecellspainter.h"

ClicableRenderArea::ClicableRenderArea(QWidget *parent, Cellular *cellular, int one_side_length)
    : RenderArea(parent, cellular, one_side_length) {}

void ClicableRenderArea::mousePressEvent(QMouseEvent *event) {
    int x, y;
    int inner_x, inner_y;
    if (event->x() < topLayerXSeek()) {
        inner_y = 0;

        x = event->x() / oneSideLength();
        if (x >= _cellular->numX()) return;
//        inner_seek_x = event->x() % oneSideLength();
        inner_x = (event->x() % oneSideLength()) / oneSideLength();

        int real_y = event->y();
        if (x % 2 != 0) real_y -= oneSideLength();
        if (real_y < 0) return;

        y = real_y / (2 * oneSideLength());
        if (y >= _cellular->numY()) return;
//        inner_seek_y = real_y % (2 * oneSideLength());
    } else {
        inner_y = 1;

        int real_y = event->y() - topLayerYSeek();
        if (real_y < 0) return;
        y = real_y / oneSideLength();
        if (y >= _cellular->numY() * 2) return;
//        inner_seek_y = real_y % oneSideLength();

        int real_x = event->x() - topLayerXSeek();
        if (y % 2 != 0) real_x -= oneSideLength();
        if (real_x < 0) return;

        x = real_x / (2 * oneSideLength());
        if (x >= _cellular->numX() * 0.5) return;
//        inner_seek_x = real_x % (2 * oneSideLength());
        inner_x = (real_x % (2 * oneSideLength())) / oneSideLength();

        x *= 2;
        if (y % 2 != 0) x += 1;
        y *= 0.5;
    }

    ClicableComplexCell *complex_cell = static_cast<ClicableComplexCell *>(_cellular->cell(x, y));
    ClicableSimpleCell *simple_cell = static_cast<ClicableSimpleCell *>(complex_cell->cell(inner_x, inner_y));

    if (event->button() != Qt::RightButton) {
        simple_cell->invertState();
    } else {
        complex_cell->showInfo();
        _curr_complex_cell = complex_cell;

        simple_cell->showInfo();
        _curr_simple_cell = simple_cell;
    }

    update();
}

void ClicableRenderArea::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() != Qt::RightButton) return;
    _curr_complex_cell->hideInfo();
    _curr_simple_cell->hideInfo();

    update();
}

void ClicableRenderArea::paintEvent(QPaintEvent *) {
    QPainter qpainter(this);
    ClicableCellsPainter cells_painter(this, &qpainter);
    drawCellular(&qpainter, &cells_painter);
}
