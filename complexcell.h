#ifndef COMPLEXCELL_H
#define COMPLEXCELL_H

#include "cell.h"
#include "simplecell.h"
#include "cellsfactory.h"

class ComplexCell : virtual public Cell<ComplexCell, 8>
{
public:
    ComplexCell(const CellsFactory *cells_factory, int x, int y);
    virtual ~ComplexCell();

    void resolvNextState();
    void next();
    void store(CellsVisitor *visitor) { visitor->visitComplexCell(*this); }

    void resetDimers();
    void initNestedNeighbours();

    // для посетителей
    int x() const { return _x; }
    int y() const { return _y; }
    SimpleCell *cell(int x, int y) { return _cells[y][x]; }

private:
    int _x, _y;
    SimpleCell *_cells[2][2];
};

#endif // COMPLEXCELL_H
