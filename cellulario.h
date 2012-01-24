#ifndef CELLULARIO_H
#define CELLULARIO_H

#include "hascellular.h"
#include "cellsvisitor.h"

class CellularIO : public HasCellular
{
protected:
    CellularIO(Cellular *cellular) : HasCellular(cellular) {}

    virtual CellsVisitor *createVisitor() = 0;

private:
    CellularIO(const CellularIO &);
    CellularIO &operator= (const CellularIO &);
};

#endif // CELLULARIO_H
