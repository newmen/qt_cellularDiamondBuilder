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

private:
    CellularReseter(const CellularReseter &);
    CellularReseter &operator= (const CellularReseter &);
};

#endif // CELLULARRESETER_H
