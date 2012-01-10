#ifndef CELL_H
#define CELL_H

template<class CellClass, int NNeighbours>
class Cell
{
public:
    virtual void resolvNextState() = 0;
    virtual void next() = 0;

    void setNeighbour(int index, CellClass* pcell) {
        _neighbours[index] = pcell;
    }

protected:
    Cell() {}

    int neighbours_num() const { return NNeighbours; }
    CellClass* neighbour(int index) const { return _neighbours[index]; }

private:
    CellClass* _neighbours[NNeighbours];
};

#endif // CELL_H
