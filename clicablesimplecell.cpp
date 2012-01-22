#include "clicablesimplecell.h"

bool ClicableSimpleCell::topIs() const {
    if (state() == 0) return false;
    else {
        if (typedNeighbour(6) == 0 /*|| typedNeighbour(7) == 0*/) return false;
        else return typedNeighbour(6)->state() == 1 || typedNeighbour(7)->state() == 1;
    }
}

bool ClicableSimpleCell::bottomIs() const {
    return typedNeighbour(4) == 0 || /*typedNeighbour(5) == 0 ||*/
            typedNeighbour(4)->state() == 1 || typedNeighbour(5)->state() == 1;
}
