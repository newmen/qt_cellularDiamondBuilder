#ifndef COMPLEXCELL_H
#define COMPLEXCELL_H

#include "cell.h"
#include "displayed.h"
#include "simplecell.h"
#include "singlerect.h"
#include "singlecolortool.h"

#define NUMBER_OF_SIMPLE_CELLS 2

class ComplexCell : public Cell<ComplexCell>, public Displayed
{
public:
    ComplexCell();

    void initNestedNeighbours();

    void resolvNextState();
    void next();

    void draw(QPainter *ppainter, int x, int y) const;

    SimpleCell* first() { return &_cells[0]; }
    SimpleCell* last() { return &_cells[1]; }

    void invertState(int x_seek, int y_seek);

    void resetDimers();

private:
    SimpleCell _cells[NUMBER_OF_SIMPLE_CELLS];

    QRect* _prect;
    QBrush* _pbrush;
    QPen* _ppen;
};

#endif // COMPLEXCELL_H
