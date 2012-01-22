#include "clicablesimplecell.h"

bool ClicableSimpleCell::bottomIs() const {
    return typedNeighbour(4) == 0 || /*typedNeighbour(5) == 0 ||*/
            typedNeighbour(4)->state() || typedNeighbour(5)->state();
}
