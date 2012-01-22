#ifndef CLICABLESIMPLECELL_H
#define CLICABLESIMPLECELL_H

#include "clicablecell.h"
#include "simplecell.h"

class ClicableSimpleCell : public ClicableCell, public SimpleCell
{
public:
    ClicableSimpleCell(int state, int x, int y) : SimpleCell(state, x, y) {}
    void invertState() { setState(1 - state()); }

    bool topIs() const;
    bool bottomIs() const;

private:
    ClicableSimpleCell(const ClicableSimpleCell &);
    ClicableSimpleCell &operator= (const ClicableSimpleCell &);
};

#endif // CLICABLESIMPLECELL_H
