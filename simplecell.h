#ifndef SIMPLECELL_H
#define SIMPLECELL_H

#include "cell.h"
#include "displayed.h"

//#include "hydrocarbon.h"

#include "singlerect.h"
#include "singlecolortool.h"

class SimpleCell : public Cell<SimpleCell, 8>, public Displayed
{
public:
    enum DimerDirect { NONE, DOWN, UP, RIGHT, LEFT };

    SimpleCell();
//    virtual ~SimpleCell();

    void resolvNextState();
    void next();

    void draw(QPainter *ppainter, int x, int y) const;

    void invertState();

    SimpleCell* top() const { return neighbour(0); }
    SimpleCell* bottom() const { return neighbour(4); }

    bool canBeDimer() const { return _state == 1; }
    void setDimerDirection(DimerDirect direct) { _dimer = direct; }
    void resetDimer() { _dimer = NONE; }

private:
    int _state, _next_state;
//    HydroCarbon* _hc;

    QRect *_prect;
    QBrush *_pbrush0, *_pbrush1;
    QPen *_ppen, *_pdimer_pen;

    DimerDirect _dimer;
};

#endif // SIMPLECELL_H
