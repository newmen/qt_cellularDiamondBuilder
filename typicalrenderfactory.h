#ifndef TYPICALRENDERFACTORY_H
#define TYPICALRENDERFACTORY_H

#include "typicalcellsfactory.h"
#include "renderfactory.h"
#include "renderarea.h"
#include "renderarea3d.h"

class TypicalRenderFactory : public TypicalCellsFactory, public RenderFactory
{
public:
    TypicalRenderFactory(int cellular_num_x, int cellular_num_y, int cellular_num_z)
        : RenderFactory(cellular_num_x, cellular_num_y, cellular_num_z) {}

    RenderArea *makeRenderArea(QWidget *parent, int curr_cellular_z, int one_side_length) {
        return new RenderArea(parent, cellularInstance(), curr_cellular_z, one_side_length);
    }

    RenderArea3D *makeRenderArea3D(QWidget *parent, int curr_cellular_z, int area_size) {
        return new RenderArea3D(parent, cellularInstance(), curr_cellular_z, area_size);
    }

private:
    TypicalRenderFactory(const TypicalRenderFactory &);
    TypicalRenderFactory &operator= (const TypicalRenderFactory &);
};

#endif // TYPICALRENDERFACTORY_H
