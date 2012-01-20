#include "renderarea.h"

RenderArea::RenderArea(QWidget *parent, Cellular *cellular, int z, int one_side_length)
    : QWidget(parent), RenderAreaI(cellular, z), _one_side_length(one_side_length) {}

//RenderArea::~RenderArea() {}

int RenderArea::width() const {
    return topLayerXSeek() + (cellular()->dimX() + 1) * _one_side_length;
}

int RenderArea::height() const {
    return (2 * cellular()->dimY() + 1) * _one_side_length;
}

QSize RenderArea::minimumSizeHint() const {
    return QSize(width(), height());
}

void RenderArea::paintEvent(QPaintEvent *) {
    QPainter qpainter(this);
    CellsPainter cells_painter(this, &qpainter);
    drawCellular(&qpainter, &cells_painter);
}

void RenderArea::drawCellular(QPainter *qpainter, CellsPainter *cells_painter) {
    qpainter->setRenderHint(QPainter::Antialiasing, true);
    cellular()->storeSlice(currZ(), cells_painter);
    qpainter->setRenderHint(QPainter::Antialiasing, false);
}
