#ifndef DISPLAYED_H
#define DISPLAYED_H

#include <QtGui>

class Displayed
{
public:
    virtual void draw(QPainter* ppainter, int x, int y) const = 0;

protected:
    Displayed() { }
};

#endif // DISPLAYED_H
