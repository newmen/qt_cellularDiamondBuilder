#ifndef CELLSFACTORY_H
#define CELLSFACTORY_H

class ComplexCell;
class SimpleCell;

class CellsFactory
{
public:
    virtual ComplexCell *createComplexCell(int x, int y) const = 0;
    virtual SimpleCell *createSimpleCell(int x, int y) const = 0;

protected:
    CellsFactory() {}
};

#endif // CELLSFACTORY_H
