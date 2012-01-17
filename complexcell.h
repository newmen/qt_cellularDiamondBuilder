#ifndef COMPLEXCELL_H
#define COMPLEXCELL_H

#include "cell.h"
#include "simplecell.h"

typedef SimpleCell SimpleCellType; // TODO : ВРЕМЕННАЯ ШЛЯПА!!

//template<class SimpleCellType = SimpleCell>
//class ComplexCell : virtual public Cell<ComplexCell<SimpleCellType>, 8>
class ComplexCell : virtual public Cell<ComplexCell, 8>
{
public:
    typedef SimpleCellType InnerCellType;

    ComplexCell(int x, int y);
    virtual ~ComplexCell();

    void resolvNextState();
    void next();
    void store(CellVisitor *visitor) { visitor->visitComplexCell(*this); }

    void resetDimers();
    void initNestedNeighbours();

    // для посетителей
    int x() const { return _x; }
    int y() const { return _y; }
    SimpleCellType *cell(int x, int y) const { return _cells[y][x]; }

private:
    SimpleCellType *cell(int x, int y) { return _cells[y][x]; }

    int _x, _y;
    SimpleCellType *_cells[2][2];
};

#endif // COMPLEXCELL_H
