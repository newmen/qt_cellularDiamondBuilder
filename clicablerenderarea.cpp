#include "clicablerenderarea.h"
#include "clicablecellspainter.h"

ClicableRenderArea::ClicableRenderArea(QWidget *parent, Cellular *cellular, int z, int one_side_length)
    : RenderArea(parent, cellular, z, one_side_length), _curr_complex_cell(0), _curr_simple_cell(0) {}

void ClicableRenderArea::mousePressEvent(QMouseEvent *event) {
    int x, y;
    int inner_x, inner_y;
    if (event->x() < topLayerXSeek()) {
        inner_y = 0;

        x = event->x() / oneSideLength();
        if (x >= cellular()->dimX()) return;
//        inner_seek_x = event->x() % oneSideLength();

        int real_y = event->y();
        if (x % 2 != 0) real_y -= oneSideLength();
        if (real_y < 0) return;

        y = real_y / (2 * oneSideLength());
        if (y >= cellular()->dimY()) return;
//        inner_seek_y = real_y % (2 * oneSideLength());
        inner_x = (real_y % (2 * oneSideLength())) / oneSideLength();
    } else {
        inner_y = 1;

        int real_y = event->y() - topLayerYSeek();
        if (real_y < 0) return;
        y = real_y / oneSideLength();
        if (y >= cellular()->dimY() * 2) return;
//        inner_seek_y = real_y % oneSideLength();

        int real_x = event->x() - topLayerXSeek();
        if (y % 2 != 0) real_x -= oneSideLength();
        if (real_x < 0) return;

        x = real_x / (2 * oneSideLength());
        if (x >= cellular()->dimX() * 0.5) return;
//        inner_seek_x = real_x % (2 * oneSideLength());
        inner_x = (real_x % (2 * oneSideLength())) / oneSideLength();

        x *= 2;
        if (y % 2 != 0) x += 1;
        y *= 0.5;
    }

    ClicableComplexCell *complex_cell = static_cast<ClicableComplexCell *>(cellular()->cell(x, y, currZ()));
    ClicableSimpleCell *simple_cell = static_cast<ClicableSimpleCell *>(complex_cell->cell(inner_x, inner_y));

    if (event->button() != Qt::RightButton && simple_cell->bottomIs() && !simple_cell->topIs()) {
        simple_cell->invertState();

        emit cellStateChanged();
        update();
    } else if (event->button() == Qt::RightButton) {
        complex_cell->showInfo();
        _curr_complex_cell = complex_cell;

        simple_cell->showInfo();
        _curr_simple_cell = simple_cell;

        emit showInfo();
        update();
    }

}

void ClicableRenderArea::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() != Qt::RightButton) return;
    _curr_complex_cell->hideInfo();
    _curr_simple_cell->hideInfo();
    emit hideInfo();

    update();
}

CellsPainter *ClicableRenderArea::createCellsPainter(QPainter *qpainter) {
    return new ClicableCellsPainter(this, qpainter);
}
