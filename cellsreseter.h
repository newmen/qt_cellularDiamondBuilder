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
    bool _is_lower_layer;
};

#endif // CELLSRESETER_H
