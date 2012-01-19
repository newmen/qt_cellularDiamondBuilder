#ifndef CLICABLESIMPLECELL_H
#define CLICABLESIMPLECELL_H

#include "clicablecell.h"
#include "simplecell.h"

class ClicableSimpleCell : public ClicableCell, public SimpleCell
{
public:
    ClicableSimpleCell(int state, int x, int y) : SimpleCell(state, x, y) {}
    void invertState() { setState(1 - state()); }
};

#endif // CLICABLESIMPLECELL_H
