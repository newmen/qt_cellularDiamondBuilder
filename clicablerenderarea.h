#ifndef CLICABLERENDERAREA_H
#define CLICABLERENDERAREA_H

#include "renderarea.h"
#include "clicablecomplexcell.h"
#include "clicablesimplecell.h"

class ClicableRenderArea : public RenderArea
{
    Q_OBJECT
public:
    ClicableRenderArea(QWidget *parent, Cellular *cellular, int one_side_length);

    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

protected:
    CellsVisitor *createVisitor();

signals:
    void cellStateChanged();
    void showInfo();
    void hideInfo();

private:
    ClicableRenderArea(const ClicableRenderArea &);
    ClicableRenderArea &operator= (const ClicableRenderArea &);

    ClicableComplexCell *_curr_complex_cell;
    ClicableSimpleCell *_curr_simple_cell;
};

#endif // CLICABLERENDERAREA_H
