#ifndef RENDERFACTORY_H
#define RENDERFACTORY_H

#include <QWidget>
#include "cellsfactory.h"
#include "cellular.h"
#include "common.h"

class RenderArea;
class RenderArea3D;

class RenderFactory : public virtual CellsFactory
{
public:
    ~RenderFactory();

    virtual RenderArea *makeRenderArea(QWidget *parent, int curr_cellular_z, int one_side_length) = 0;
    virtual RenderArea3D *makeRenderArea3D(QWidget *parent, int curr_cellular_z, int area_size) = 0;

    Cellular *cellularInstance();

protected:
    RenderFactory(int cellular_num_x, int cellular_num_y, int cellular_num_z)
        : _single_cellular(0), _cellular_dims(cellular_num_x, cellular_num_y, cellular_num_z) {}

private:
    Cellular *_single_cellular;
    dim3 _cellular_dims;
};

#endif // RENDERFACTORY_H
