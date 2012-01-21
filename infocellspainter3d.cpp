#include "infocellspainter3d.h"

InfoCellsPainter3D::InfoCellsPainter3D(InfoRenderArea3D *clicable_render_area_3d, int cellular_dim_y)
    : CellsPainter3D(clicable_render_area_3d, cellular_dim_y), _show_info(false), _curr_complex_cell_info(ClicableCell::HIDE) {}

void InfoCellsPainter3D::visitComplexCell(ComplexCell &cell) {
    if (_show_info) {
        ClicableCell &clicable_cell = dynamic_cast<ClicableCell &>(cell);
        _curr_complex_cell_info = clicable_cell.info();
    }

    CellsPainter3D::visitComplexCell(cell);
}

void InfoCellsPainter3D::visitSimpleCell(SimpleCell &cell) {
    if (cell.state() == 1) {
        float alpha;
        if (_show_info) {
            switch (_curr_complex_cell_info) {
            case ClicableCell::SHOW:
                alpha = 1.f;
                break;
            case ClicableCell::NEIGHBOUR:
                alpha = .67f;
                break;
            default:
                alpha = .067f;
            }
        } else {
            alpha = 1.f;
        }

        drawSimpleCellCube(cell, alpha);
    }

    ClicableCell &clicable_cell = dynamic_cast<ClicableCell &>(cell);
    if (clicable_cell.info() == ClicableCell::HIDE) return;

    float info_alpha;
    switch (_curr_complex_cell_info) {
    case ClicableCell::SHOW:
        info_alpha = .5f;
        break;
    case ClicableCell::NEIGHBOUR:
        info_alpha = .25f;
        break;
    }

    static_cast<InfoRenderArea3D *>(renderArea())->drawInfoCube(currSimpleCellPos(cell), float3(.1f, .5f, 1.f), info_alpha);
}
