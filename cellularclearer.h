#ifndef CELLULARCLEARER_H
#define CELLULARCLEARER_H

#include "cellulario.h"

class CellularClearer : public CellularIO
{
public:
    CellularClearer(Cellular *cellular) : CellularIO(cellular) {}

    void clear();

protected:
    CellsVisitor *createVisitor();
};

#endif // CELLULARCLEARER_H
