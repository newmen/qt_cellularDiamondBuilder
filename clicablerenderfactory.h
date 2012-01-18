#ifndef CLICABLERENDERFACTORY_H
#define CLICABLERENDERFACTORY_H

#include "clicablecellsfactory.h"
#include "clicablerenderarea.h"
#include "renderfactory.h"

class ClicableRenderFactory : public ClicableCellsFactory, public RenderFactory
{
public:
    ClicableRenderFactory(int cellular_num_x, int cellular_num_y) : ClicableCellsFactory(cellular_num_x, cellular_num_y) {}

    RenderArea *makeRenderArea(QWidget *parent, int one_side_length) {
        return new ClicableRenderArea(parent, makeCellular(), one_side_length);
    }
};

#endif // CLICABLERENDERFACTORY_H
