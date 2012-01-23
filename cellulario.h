#ifndef CELLULARIO_H
#define CELLULARIO_H

#include "cellular.h"
#include "cellsvisitor.h"

class CellularIO
{
public:
    virtual ~CellularIO() {}

protected:
    CellularIO(Cellular *cellular) : _cellular(cellular) {}

    Cellular *cellular() { return _cellular; }
    Cellular *cellular() const { return _cellular; }

    virtual CellsVisitor *createVisitor() = 0;

private:
    CellularIO(const CellularIO &);
    CellularIO &operator= (const CellularIO &);

    Cellular *_cellular;
};

#endif // CELLULARIO_H
