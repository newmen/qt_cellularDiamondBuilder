#ifndef CELLSFACTORY_H
#define CELLSFACTORY_H

class ComplexCell;
class SimpleCell;

class CellsFactory
{
public:
    virtual ~CellsFactory() {}

    virtual ComplexCell *makeComplexCell(int state, int x, int y, int z) const = 0;
    virtual SimpleCell *makeSimpleCell(int state, int x, int y) const = 0;

protected:
    CellsFactory() {}

private:
    CellsFactory(const CellsFactory &);
    CellsFactory &operator= (const CellsFactory &);
};

#endif // CELLSFACTORY_H
