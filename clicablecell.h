#ifndef CLICABLECELL_H
#define CLICABLECELL_H

#include "cell.h"

template<class CellType, int NNeighbours>
class ClicableCell : virtual public Cell<CellType, NNeighbours>
{
public:
    enum Info { HIDE, SHOW, NEIGHBOUR };

    ClicableCell() : _info(HIDE) {}

    Info info() const { return _info; }

    void showInfo();
    void hideInfo(bool with_neighbours = true);

private:
    void neighbourInfo() { _info = NEIGHBOUR; }

    Info _info;
};

#endif // CLICABLECELL_H
