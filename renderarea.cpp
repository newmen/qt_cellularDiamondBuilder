#include "renderarea.h"
#include "cellpainter.h"

RenderArea::RenderArea(QWidget *parent, CellularI *cellular, int one_side_length)
    : QWidget(parent), _cellular(cellular), _one_side_length(one_side_length) {}

//RenderArea::~RenderArea() {}

QSize RenderArea::minimumSizeHint() const {
    return QSize(topLayerXSeek() + (_cellular->numX() + 1) * _one_side_length,
                 (2 * _cellular->numY() + 1) * _one_side_length);
}

void RenderArea::paintEvent(QPaintEvent *) {
    drawCellular<CellPainter>();
}

void RenderArea::next() {
    _cellular->next();
    update();
}

template<class CellPainterType>
void RenderArea::drawCellular() {
    QPainter qpainter(this);
    qpainter.setRenderHint(QPainter::Antialiasing, true);

    CellPainterType cell_painter(this, &qpainter);
    _cellular->store(&cell_painter);

    qpainter.setRenderHint(QPainter::Antialiasing, false);
}
