#ifndef CELLSCLEARER_H
#define CELLSCLEARER_H

#include "cellsvisitor.h"

class CellsClearer : public CellsVisitor
{
public:
    CellsClearer() {}

    void visitComplexCell(ComplexCell &cell);
    void visitSimpleCell(SimpleCell &cell);
};

#endif // CELLSCLEARER_H
