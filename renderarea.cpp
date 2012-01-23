#include "renderarea.h"
#include "cellspainter.h"

RenderArea::RenderArea(QWidget *parent, Cellular *cellular, int one_side_length)
    : QWidget(parent), RenderAreaI(cellular), _one_side_length(one_side_length) {}

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
    // необходимо обязательно инитить _qpainter, перед созданием посетителя!
    // TODO: возможно следует переделать на shared_ptr или типа того
    _qpainter = new QPainter(this);

    CellsVisitor *cells_painter = createVisitor();

    _qpainter->setRenderHint(QPainter::Antialiasing, true);
    cellular()->storeSlice(currZ(), cells_painter);
    _qpainter->setRenderHint(QPainter::Antialiasing, false);

    delete cells_painter;
    delete _qpainter;
}

CellsVisitor *RenderArea::createVisitor() {
    return new CellsPainter(this, _qpainter);
}
