#ifndef TYPICALRENDERFACTORY_H
#define TYPICALRENDERFACTORY_H

#include "typicalcellsfactory.h"
#include "renderfactory.h"
#include "renderarea.h"

class TypicalRenderFactory : public TypicalCellsFactory, public RenderFactory
{
public:
    TypicalRenderFactory(int cellular_num_x, int cellular_num_y, int cellular_num_z)
        : TypicalCellsFactory(cellular_num_x, cellular_num_y, cellular_num_z) {}

    RenderArea *makeRenderArea(QWidget *parent, int z, int one_side_length) {
        return new RenderArea(parent, makeCellular(), z, one_side_length);
    }
};

#endif // TYPICALRENDERFACTORY_H
