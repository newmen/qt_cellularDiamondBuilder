#include "renderarea.h"

RenderArea::RenderArea(QWidget *parent, Cellular *cellular, int z, int one_side_length)
    : QWidget(parent), _cellular(cellular), _curr_z(z), _one_side_length(one_side_length) {}

//RenderArea::~RenderArea() {}

QSize RenderArea::minimumSizeHint() const {
    return QSize(topLayerXSeek() + (_cellular->numX() + 1) * _one_side_length,
                 (2 * _cellular->numY() + 1) * _one_side_length);
}

void RenderArea::paintEvent(QPaintEvent *) {
    QPainter qpainter(this);
    CellsPainter cells_painter(this, &qpainter);
    drawCellular(&qpainter, &cells_painter);
}

void RenderArea::moveZ(int z) {
     _curr_z = z;
     update();
}

void RenderArea::drawCellular(QPainter *qpainter, CellsPainter *cells_painter) {
    qpainter->setRenderHint(QPainter::Antialiasing, true);
    _cellular->storeSlice(currZ(), cells_painter);
    qpainter->setRenderHint(QPainter::Antialiasing, false);
}
