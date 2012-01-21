#ifndef RENDERFACTORY_H
#define RENDERFACTORY_H

#include <QWidget>
#include "singlecellularfactory.h"

class RenderArea;
class RenderArea3D;

class RenderFactory : public virtual SingleCellularFactory
{
public:
    virtual ~RenderFactory() {}

    virtual RenderArea *makeRenderArea(QWidget *parent, int curr_cellular_z, int one_side_length) = 0;
    virtual RenderArea3D *makeRenderArea3D(QWidget *parent, int curr_cellular_z, int area_size) = 0;

protected:
    RenderFactory() {}
};

#endif // RENDERFACTORY_H
