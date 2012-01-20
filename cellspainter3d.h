#ifndef CELLSPAINTER3D_H
#define CELLSPAINTER3D_H

#include "cellsvisitor.h"
#include "common.h"

class RenderArea3D;

class CellsPainter3D : public CellsVisitor
{
public:
    CellsPainter3D(RenderArea3D *render_area_3d, int cellular_dim_y);

    void visitComplexCell(ComplexCell &cell);
    void visitSimpleCell(SimpleCell &cell);

private:
    RenderArea3D *_render_area;
    int _cellular_max_y;
    float3 _color;
    float3 _seek;
};

#endif // CELLSPAINTER3D_H