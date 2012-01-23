#ifndef SIMPLECELL_H
#define SIMPLECELL_H

#include "cell.h"

//#include "hydrocarbon.h"

class SimpleCell : public Cell<SimpleCell, 8>
{
public:
    enum DimerDirection { NONE, FRONT, BACK };

    SimpleCell(int state, int x, int y);
//    virtual ~SimpleCell();

    void resolvNextState();
    void next();
    void store(CellsVisitor *visitor) { visitor->visitSimpleCell(*this); }

    SimpleCell *front() const { return typedNeighbour(0); }

    bool topFrontIs() const;

    bool canBeDimer() const { return _state == 1; }
    void setDimerDirection(DimerDirection direct) { _dimer = direct; }
    void resetDimer() { _dimer = NONE; }

    // для посетителей
    int x() const { return _x; }
    int y() const { return _y; }
    DimerDirection dimer() const { return _dimer; }
    int state() const { return _state; }
    void setState(int state) { _state = state; }

private:
    SimpleCell(const SimpleCell &);
    SimpleCell &operator= (const SimpleCell &);

    int _x, _y;
    int _state, _next_state;
//    HydroCarbon* _hc;

    DimerDirection _dimer;
};

#endif // SIMPLECELL_H
