#ifndef SIMPLECELL_H
#define SIMPLECELL_H

#include "cell.h"
#include "displayed.h"

//#include "hydrocarbon.h"

#include "singlerect.h"
#include "singlecolortool.h"

class SimpleCell : public Cell<SimpleCell>, public Displayed
{
public:
    SimpleCell();
//    virtual ~SimpleCell();

    void resolvNextState();
    void next();

    void draw(QPainter *ppainter, int x, int y) const;

    void invertState();

    SimpleCell* top() const { return neighbour(0); }
    SimpleCell* bottom() const { return neighbour(4); }

    bool canBeDimer() const { return _state == 1; }
    void dimer(int value) { _dimer = value; }
    void resetDimer() { _dimer = -1; }

private:
    int _state, _next_state;
//    HydroCarbon* _hc;

    QRect* _prect;
    QBrush* _pbrush0;
    QBrush* _pbrush1;
    QPen* _ppen;

    int _dimer;
};

#endif // SIMPLECELL_H
