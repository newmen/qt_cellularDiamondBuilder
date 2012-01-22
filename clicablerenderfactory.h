#ifndef CLICABLERENDERFACTORY_H
#define CLICABLERENDERFACTORY_H

#include "renderfactory.h"
#include "clicablecellsfactory.h"
#include "clicablerenderarea.h"
#include "inforenderarea3d.h"

class ClicableRenderFactory : public ClicableCellsFactory, public RenderFactory
{
public:
    ClicableRenderFactory(int cellular_num_x, int cellular_num_y, int cellular_num_z)
        : RenderFactory(cellular_num_x, cellular_num_y, cellular_num_z) {}

    RenderArea *makeRenderArea(QWidget *parent, int curr_cellular_z, int one_side_length) {
        return new ClicableRenderArea(parent, cellularInstance(), curr_cellular_z, one_side_length);
    }

    RenderArea3D *makeRenderArea3D(QWidget *parent, int curr_cellular_z, int area_size) {
        return new InfoRenderArea3D(parent, cellularInstance(), curr_cellular_z, area_size);
    }

private:
    ClicableRenderFactory(const ClicableRenderFactory &);
    ClicableRenderFactory &operator= (const ClicableRenderFactory &);
};

#endif // CLICABLERENDERFACTORY_H
