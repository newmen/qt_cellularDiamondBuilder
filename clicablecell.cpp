#include "clicablecell.h"

void ClicableCell::showInfo() {
    _info = SHOW;
    for (int i = 0; i < neighboursNum(); ++i) {
        clicableNeighbour(i)->neighbourInfo();
    }
}

void ClicableCell::hideInfo(bool with_neighbours) {
    _info = HIDE;
    if (!with_neighbours) return;
    for (int i = 0; i < neighboursNum(); ++i) {
        clicableNeighbour(i)->hideInfo(false);
    }
}
