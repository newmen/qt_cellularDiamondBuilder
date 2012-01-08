#ifndef CELL_H
#define CELL_H

template<class CellClass>
class Cell
{
public:
    virtual ~Cell() {
        delete [] _neighbours;
    }

    virtual void resolvNextState() = 0;
    virtual void next() = 0;

    void setNeighbour(int index, CellClass* pcell) {
        _neighbours[index] = pcell;
    }

protected:
    Cell(int neighbours_num) : _neighbours_num(neighbours_num) {
        _neighbours = new CellClass*[_neighbours_num];
    }

    int neighbours_num() const { return _neighbours_num; }
    CellClass* neighbour(int index) const { return _neighbours[index]; }

private:
    Cell();

    CellClass** _neighbours;
    const int _neighbours_num;
};

#endif // CELL_H
