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
    enum Info { HIDE, SHOW, NEIGHBOUR };

    ComplexCell();

    void initNestedNeighbours();

    void resolvNextState();
    void next();

    void draw(QPainter *ppainter, int x, int y) const;

    SimpleCell *first(Part part_index) { return &_cells[2 * part_index]; }
    SimpleCell *last(Part part_index) { return &_cells[2 * part_index + 1]; }

    void invertState(Part part, int x_seek, int y_seek);

    void resetDimers();

    void showInfo();
    void hideInfo(bool with_neighbours = true);

private:
    void neighbourInfo() { _info = NEIGHBOUR; }

    SimpleCell _cells[NUMBER_OF_SIMPLE_CELLS];

    QRect *_prect_down, *_prect_up;
    QColor *_pcolor_default, *_pcolor_info, *_pcolor_neighbour_info;
    QBrush *_pbrush;
    QPen *_ppen;

    Info _info;
};

#endif // COMPLEXCELL_H
