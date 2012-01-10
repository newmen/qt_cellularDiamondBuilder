#ifndef COMPLEXCELL_H
#define COMPLEXCELL_H

#include "cell.h"
#include "displayed.h"
#include "simplecell.h"
#include "singlerect.h"
#include "singlecolortool.h"

#define NUMBER_OF_SIMPLE_CELLS 4

class ComplexCell : public Cell<ComplexCell, 8>, public Displayed
{
public:
    enum Part { DOWN = 0, UP };

    ComplexCell();

    void initNestedNeighbours();

    void resolvNextState();
    void next();

    void draw(QPainter *ppainter, int x, int y) const;

    SimpleCell *first(Part part_index) { return &_cells[2 * part_index]; }
    SimpleCell *last(Part part_index) { return &_cells[2 * part_index + 1]; }

    void invertState(Part part, int x_seek, int y_seek);

    void resetDimers();

private:
    SimpleCell _cells[NUMBER_OF_SIMPLE_CELLS];

    QRect *_prect_down, *_prect_up;
    QBrush *_pbrush;
    QPen *_ppen;
};

#endif // COMPLEXCELL_H
