#ifndef RENDERAREA3D_H
#define RENDERAREA3D_H

#include <QGLViewer/qglviewer.h>
#include "renderareai.h"
#include "cellular.h"
#include "common.h"
#include "cellspainter3d.h"

class RenderArea3D : public QGLViewer, public RenderAreaI
{
    Q_OBJECT
public:
    RenderArea3D(QWidget *parent, Cellular *cellular, int z, int area_size);
    ~RenderArea3D();

    int width() const { return _area_size; }
    int height() const { return _area_size; }
    QSize minimumSizeHint() const;

    void drawCube(const float3 &center, const float3 &color, float alpha);
    void drawCubeBorder(const float3 &center, const float3 &color, float alpha);
    void drawBCube(const float3 &center, const float3 &color, float alpha);

    void drawHalfDimer(const float3 &center, float alpha);

protected:
    void init();
    void draw();

    virtual CellsPainter3D *createCellsPainter();
    CellsPainter3D *cellsPainter() { return _cells_painter; }

    void primitiveCube(const float3 &center, float half_side_length, const float3 &color, float alpha);
    void primitiveCubeBorder(const float3 &center, float half_side_length, const float3 &color, float alpha);

    void primitiveParallelepiped(const float3 &center, const float3 &half_side_lengths, const float3 &color, float alpha);
    void primitiveParallelepipedBorder(const float3 &center, const float3 &half_side_lengths, float border_width,
                                      const float3 &color, float alpha);

signals:

public slots:

private:
    void setColor(const float3 &color, float alpha) { glColor4f(color.x, color.y, color.z, alpha); }
    void drawSliceSelector();
    void setRadiusAndCenter();

    Cellular *_cellular;
    int _area_size;

    CellsPainter3D *_cells_painter;
};

#endif // RENDERAREA3D_H
