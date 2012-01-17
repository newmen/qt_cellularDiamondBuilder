#ifndef CLICABLESIMPLECELL_H
#define CLICABLESIMPLECELL_H

#include "clicablecell.h"
#include "simplecell.h"

class ClicableSimpleCell : public ClicableCell<SimpleCell, 8>, public SimpleCell
{
public:
    ClicableSimpleCell(int x, int y) : SimpleCell(x, y) {}
    void invertState() { setState(1 - state()); }
};

#endif // CLICABLESIMPLECELL_H
