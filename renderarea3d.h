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
    RenderArea3D(QWidget *parent, Cellular *cellular, int z, int area_size);

    int width() const { return _area_size; }
    int height() const { return _area_size; }
    QSize minimumSizeHint() const;

    void drawCube(const float3 &center, const float3 &color, float alpha = 1.f);
    void drawCubeWF(const float3 &center, const float3 &color, float alpha = 1.f);
    void drawBCube(const float3 &center, const float3 &color, float alpha = 1.f);

    void drawHalfDimer(const float3 &center);

protected:
    void init();
    void draw();

signals:

public slots:

private:
    void setColor(const float3 &color, float alpha) { glColor4f(color.x, color.y, color.z, alpha); }
    void drawSliceSelector();
    void setRadiusAndCenter();

    Cellular *_cellular;
    int _area_size;
};

#endif // RENDERAREA3D_H
