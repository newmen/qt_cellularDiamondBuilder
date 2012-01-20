#ifndef CLICABLERENDERFACTORY_H
#define CLICABLERENDERFACTORY_H

#include "clicablecellsfactory.h"
#include "clicablerenderarea.h"
#include "renderfactory.h"

class ClicableRenderFactory : public ClicableCellsFactory, public RenderFactory
{
public:
    ClicableRenderFactory(int cellular_num_x, int cellular_num_y, int cellular_num_z)
        : ClicableCellsFactory(cellular_num_x, cellular_num_y, cellular_num_z) {}

    RenderArea *makeRenderArea(QWidget *parent, int curr_cellular_z, int one_side_length) {
        return new ClicableRenderArea(parent, cellularInstance(), curr_cellular_z, one_side_length);
    }
};

#endif // CLICABLERENDERFACTORY_H
