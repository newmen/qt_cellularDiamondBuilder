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

private:
    CellularClearer(const CellularClearer &);
    CellularClearer &operator= (const CellularClearer &);
};

#endif // CELLULARCLEARER_H
