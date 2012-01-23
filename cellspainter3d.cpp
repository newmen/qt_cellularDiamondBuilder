#include "cellspainter3d.h"
#include "renderarea3d.h"
#include "complexcell.h"
#include "simplecell.h"

CellsPainter3D::CellsPainter3D(RenderArea3D *render_area_3d, int cellular_max_y)
    : _render_area(render_area_3d), _cellular_max_y(cellular_max_y), _color(.2f, .8f, .3f) {}

void CellsPainter3D::visitComplexCell(ComplexCell &cell) {
    const int3 &pos = cell.pos();
    float slice_seek = pos.z * .5f;
    _seek(slice_seek + pos.x, slice_seek + pos.y * 2, pos.z * _render_area->cellHeight() * 2);
    if (cell.x() % 2 != 0) _seek.y += 1;

    for (int y = 0; y < 2; ++y) {
        for (int x = 0; x < 2; ++x) cell.cell(x, y)->store(this);
    }
}

void CellsPainter3D::visitSimpleCell(SimpleCell &cell) {
    if (cell.state() != 1) return;
    drawSimpleCell(cell);
}

float3 CellsPainter3D::currSimpleCellPos(const SimpleCell &cell) const {
    float3 pos = _seek;
    if (cell.y() == 0) {
        pos.y += cell.x();
    } else {
        pos.z += _render_area->cellHeight();
        pos.y += .5f;
        pos.x += cell.x();
    }
    pos.y = _cellular_max_y - pos.y;

    return pos;
}

void CellsPainter3D::drawSimpleCell(const SimpleCell &cell, float alpha) {
    float3 pos = currSimpleCellPos(cell);
    _render_area->drawBCell(pos, _color, alpha);

    if (cell.dimer() == SimpleCell::NONE) return;

    float dimer_seek = ((cell.dimer() == SimpleCell::FRONT) ? -.25f : .25f);
    if (cell.y() == 0) pos.y -= dimer_seek;
    else pos.x += dimer_seek;
    pos.z += .5f * _render_area->cellHeight();

    _render_area->drawHalfDimer(pos, alpha * .78f);
}
