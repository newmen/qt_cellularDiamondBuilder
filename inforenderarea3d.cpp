#include "inforenderarea3d.h"
#include "infocellspainter3d.h"

InfoRenderArea3D::InfoRenderArea3D(QWidget *parent, Cellular *cellular, int z, int area_size)
    : RenderArea3D(parent, cellular, z, area_size) {}

void InfoRenderArea3D::drawInfoCube(const float3 &center, const float3 &color, float alpha) {
    primitiveCube(center, .5f, color, alpha);
}

void InfoRenderArea3D::showInfo() {
    static_cast<InfoCellsPainter3D *>(cellsPainter())->showInfo();
    repaint();
}

void InfoRenderArea3D::hideInfo() {
    static_cast<InfoCellsPainter3D *>(cellsPainter())->hideInfo();
    repaint();
}

CellsPainter3D *InfoRenderArea3D::createCellsPainter() {
    return new InfoCellsPainter3D(this, cellular()->dimY() - 1);
}
