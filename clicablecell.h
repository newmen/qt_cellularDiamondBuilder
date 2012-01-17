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

template<class CellType, int NNeighbours>
void ClicableCell<CellType, NNeighbours>::showInfo() {
    _info = SHOW;
    ClicableCell<CellType, NNeighbours> *neighbour;
    for (int i = 0; i < this->neighboursNum(); ++i) {
        neighbour = dynamic_cast<ClicableCell<CellType, NNeighbours> *>(this->changeableNeighbour(i));
        neighbour->neighbourInfo();
    }
}

template<class CellType, int NNeighbours>
void ClicableCell<CellType, NNeighbours>::hideInfo(bool with_neighbours) {
    _info = HIDE;
    if (!with_neighbours) return;
    ClicableCell<CellType, NNeighbours> *neighbour;
    for (int i = 0; i < this->neighboursNum(); ++i) {
        neighbour = dynamic_cast<ClicableCell<CellType, NNeighbours> *>(this->changeableNeighbour(i));
        neighbour->neighbourInfo();
    }
}

#endif // CLICABLECELL_H
