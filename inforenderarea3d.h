#ifndef INFORENDERAREA3D_H
#define INFORENDERAREA3D_H

#include "renderarea3d.h"

class InfoRenderArea3D : public RenderArea3D
{
    Q_OBJECT
public:
    InfoRenderArea3D(QWidget *parent, Cellular *cellular, int area_size);
    ~InfoRenderArea3D() {}

    void drawInfoCell(const float3 &center, const float3 &color, float alpha);

public slots:
    void showInfo();
    void hideInfo();

protected:
   CellsVisitor *createVisitor();

private:
   InfoRenderArea3D(const InfoRenderArea3D &);
   InfoRenderArea3D &operator= (const InfoRenderArea3D &);
};

#endif // INFORENDERAREA3D_H
