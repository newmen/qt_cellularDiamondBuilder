#ifndef CLICABLERENDERAREA_H
#define CLICABLERENDERAREA_H

#include "renderarea.h"
#include "clicablecomplexcell.h"
#include "clicablesimplecell.h"

class ClicableRenderArea : public RenderArea
{
    Q_OBJECT
public:
    ClicableRenderArea(QWidget *parent, Cellular *cellular, int z, int one_side_length);

    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);

signals:
    void cellStateChanged();

private:
    ClicableComplexCell *_curr_complex_cell;
    ClicableSimpleCell *_curr_simple_cell;
};

#endif // CLICABLERENDERAREA_H
