#ifndef CELLVISITOR_H
#define CELLVISITOR_H

class ComplexCell;
class SimpleCell;

class CellVisitor
{
public:
    virtual ~CellVisitor() {}

    virtual void visitComplexCell(const ComplexCell &cell) = 0;
    virtual void visitSimpleCell(const SimpleCell &cell) = 0;

protected:
    CellVisitor() {}
};

#endif // CELLVISITOR_H
