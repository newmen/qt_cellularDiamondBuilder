#ifndef COMPLEXCELL_H
#define COMPLEXCELL_H

#include "common.h"
#include "cell.h"
#include "simplecell.h"
#include "cellsfactory.h"

class ComplexCell : public Cell<ComplexCell, 8>
{
public:
    ComplexCell(const CellsFactory *cells_factory, int state, int x, int y, int z);
    ~ComplexCell();

    void resolvNextState();
    void next();
    void store(CellsVisitor *visitor) { visitor->visitComplexCell(*this); }

    void resetDimers();
    void initNestedNeighbours();

    // для посетителей
    int x() const { return _pos.x; }
    int y() const { return _pos.y; }
    int z() const { return _pos.z; }
    SimpleCell *cell(int x, int y) { return _cells[y][x]; }

private:
    SimpleCell *bottomFirstCell() { return _cells[0][0]; }
    SimpleCell *bottomSecondCell() { return _cells[0][1]; }
    SimpleCell *topFirstCell() { return _cells[1][0]; }
    SimpleCell *topSecondCell() { return _cells[1][1]; }

    int3 _pos;
    SimpleCell *_cells[2][2];
};

#endif // COMPLEXCELL_H
