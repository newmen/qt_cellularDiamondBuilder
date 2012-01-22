#ifndef INFOCELLSPAINTER3D_H
#define INFOCELLSPAINTER3D_H

#include "cellspainter3d.h"
#include "inforenderarea3d.h"
#include "clicablecell.h"

class InfoCellsPainter3D : public CellsPainter3D
{
public:
    InfoCellsPainter3D(InfoRenderArea3D *clicable_render_area_3d, int cellular_dim_y);

    void showInfo() { _show_info = true; }
    void hideInfo() { _show_info = false; }

    void visitComplexCell(ComplexCell &cell);
    void visitSimpleCell(SimpleCell &cell);

private:
    InfoCellsPainter3D(const InfoCellsPainter3D &);
    InfoCellsPainter3D &operator= (const InfoCellsPainter3D &);

    bool _show_info;
    ClicableCell::Info _curr_complex_cell_info;
};

#endif // INFOCELLSPAINTER3D_H
