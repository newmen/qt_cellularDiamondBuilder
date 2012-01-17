#include "clicablerenderarea.h"
#include "clicablecellpainter.h"
#include "cellular.h"

ClicableRenderArea::ClicableRenderArea(QWidget *parent, CellularI *cellular, int one_side_length)
    : RenderArea(parent, cellular, one_side_length) {}

void ClicableRenderArea::mousePressEvent(QMouseEvent *event) {
    int x, y;
    int inner_x, inner_y;
    if (event->x() < topLayerXSeek()) {
        inner_y = 0;

        x = event->x() / oneSideLength();
        if (x >= cellular()->numX()) return;
//        inner_seek_x = event->x() % oneSideLength();
        inner_x = (event->x() % oneSideLength()) / oneSideLength();

        int real_y = event->y();
        if (x % 2 != 0) real_y -= oneSideLength();
        if (real_y < 0) return;

        y = real_y / (2 * oneSideLength());
        if (y >= cellular()->numY()) return;
//        inner_seek_y = real_y % (2 * oneSideLength());
    } else {
        inner_y = 1;

        int real_y = event->y() - topLayerYSeek();
        if (real_y < 0) return;
        y = real_y / oneSideLength();
        if (y >= cellular()->numY() * 2) return;
//        inner_seek_y = real_y % oneSideLength();

        int real_x = event->x() - topLayerXSeek();
        if (y % 2 != 0) real_x -= oneSideLength();
        if (real_x < 0) return;

        x = real_x / (2 * oneSideLength());
        if (x >= cellular()->numX() * 0.5) return;
//        inner_seek_x = real_x % (2 * oneSideLength());
        inner_x = (real_x % (2 * oneSideLength())) / oneSideLength();

        x *= 2;
        if (y % 2 != 0) x += 1;
        y *= 0.5;
    }

    Cellular<ClicableComplexCell> *pcellular = dynamic_cast<Cellular<ClicableComplexCell> *>(cellular());
    if (!pcellular) return;

    ClicableComplexCell *complex_cell = pcellular->cell(x, y);
//    ClicableSimpleCell *simple_cell = complex_cell->cell(inner_x, inner_y);

    if (event->button() != Qt::RightButton) {
//        simple_cell->invertState();
    } else {
        complex_cell->showInfo();
        _curr_complex_cell = complex_cell;

//        simple_cell->showInfo();
//        _curr_simple_cell = simple_cell;
    }

    update();
}

void ClicableRenderArea::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() != Qt::RightButton) return;
    _curr_complex_cell->hideInfo();
//    _curr_simple_cell->hideInfo();

    update();
}

void ClicableRenderArea::paintEvent(QPaintEvent *) {
    drawCellular<ClicableCellPainter>();
}
