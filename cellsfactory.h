#ifndef CELLSFACTORY_H
#define CELLSFACTORY_H

class Cellular;
class ComplexCell;
class SimpleCell;

class CellsFactory
{
public:
    virtual ~CellsFactory();
    virtual Cellular *makeCellular();

    virtual ComplexCell *makeComplexCell(int x, int y) const = 0;
    virtual SimpleCell *makeSimpleCell(int x, int y) const = 0;

protected:
    CellsFactory(int cellular_num_x, int cellular_num_y)
        : _single_cellular(0), _cellular_num_x(cellular_num_x), _cellular_num_y(cellular_num_y) {}

private:
    Cellular *_single_cellular;
    int _cellular_num_x, _cellular_num_y;
};

#endif // CELLSFACTORY_H
