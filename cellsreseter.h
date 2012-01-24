#ifndef CELLSRESETER_H
#define CELLSRESETER_H

#include "cellsvisitor.h"

class CellsReseter : public CellsVisitor
{
public:
    CellsReseter() {}

    void visitComplexCell(ComplexCell &cell);
    void visitSimpleCell(SimpleCell &cell);

private:
    CellsReseter(const CellsReseter &);
    CellsReseter &operator= (const CellsReseter &);

    bool _is_lower_layer;
};

#endif // CELLSRESETER_H
