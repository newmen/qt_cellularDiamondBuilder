#ifndef CLICABLECELL_H
#define CLICABLECELL_H

#include "celli.h"

class ClicableCell : public virtual CellI
{
public:
    enum Info { HIDE, SHOW, NEIGHBOUR };

    ClicableCell() : _info(HIDE) {}

    Info info() const { return _info; }

    void showInfo();
    void hideInfo(bool with_neighbours = true);

private:
    ClicableCell(const ClicableCell &);
    ClicableCell &operator= (const ClicableCell &);

    void neighbourInfo() { _info = NEIGHBOUR; }
    ClicableCell *clicableNeighbour(int index) { return dynamic_cast<ClicableCell *>(changeableNeighbour(index)); }

    Info _info;
};

#endif // CLICABLECELL_H
