#ifndef CELLULARRESETER_H
#define CELLULARRESETER_H

#include "cellulario.h"

class CellularReseter : public CellularIO
{
public:
    CellularReseter(Cellular *cellular) : CellularIO(cellular) {}

    void reset();

protected:
    CellsVisitor *createVisitor();
};

#endif // CELLULARRESETER_H
