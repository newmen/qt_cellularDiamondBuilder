#ifndef RENDERAREA3D_H
#define RENDERAREA3D_H

#include <QGLViewer/qglviewer.h>
#include "renderareai.h"
#include "cellular.h"
#include "common.h"

class RenderArea3D : public QGLViewer, public RenderAreaI
{
    Q_OBJECT
public:
    RenderArea3D(QWidget *parent, Cellular *cellular, int area_size);
    ~RenderArea3D();

    int width() const { return _area_size; }
    int height() const { return _area_size; }
    QSize minimumSizeHint() const;

    void drawCell(const float3 &center, const float3 &color, float alpha);
    void drawCellBorder(const float3 &center, const float3 &color, float alpha);
    void drawBCell(const float3 &center, const float3 &color, float alpha);

    void drawHalfDimer(const float3 &center, float alpha);

    float cellHeight() const { return _cell_height; }

protected:
    void init();
    void draw();

    CellsVisitor *createVisitor();
    CellsVisitor *cellsPainter() { return _cells_painter; }

    void primitiveCell(const float3 &center, float half_side_length, const float3 &color, float alpha);
    void primitiveCellBorder(const float3 &center, float half_side_length, const float3 &color, float alpha);

    void primitiveParallelepiped(const float3 &center, const float3 &half_side_lengths, const float3 &color, float alpha);
    void primitiveParallelepipedBorder(const float3 &center, const float3 &half_side_lengths, float border_width,
                                      const float3 &color, float alpha);

signals:

public slots:
    void resetCamera();

private:
    RenderArea3D(const RenderArea3D &);
    RenderArea3D &operator= (const RenderArea3D &);

    void setColor(const float3 &color, float alpha) { glColor4f(color.x, color.y, color.z, alpha); }
    void drawSliceSelector();
    void setRadiusAndCenter();

    Cellular *_cellular;
    int _area_size;

    CellsVisitor *_cells_painter;

    const float _cell_height;
};

#endif // RENDERAREA3D_H
