#ifndef CELLSVISITOR_H
#define CELLSVISITOR_H

class ComplexCell;
class SimpleCell;

class CellsVisitor
{
public:
    virtual ~CellsVisitor() {}

    virtual void visitComplexCell(ComplexCell &cell) = 0;
    virtual void visitSimpleCell(SimpleCell &cell) = 0;

protected:
    CellsVisitor() {}

    void visitSimpleCells(ComplexCell &cell);

private:
    CellsVisitor(const CellsVisitor &);
    CellsVisitor &operator= (const CellsVisitor &);
};

#endif // CELLSVISITOR_H
