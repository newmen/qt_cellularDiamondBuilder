#include "clicablecell.h"

template<class CellType, int NNeighbours>
void ClicableCell<CellType, NNeighbours>::showInfo() {
    _info = SHOW;
    for (int i = 0; i < this->neighboursNum(); ++i) {
        this->changeableNeighbour(i)->neighbourInfo();
    }
}

template<class CellType, int NNeighbours>
void ClicableCell<CellType, NNeighbours>::hideInfo(bool with_neighbours) {
    _info = HIDE;
    if (!with_neighbours) return;
    for (int i = 0; i < this->neighboursNum(); ++i) {
        this->changeableNeighbour(i)->hideInfo(false);
    }
}
