#ifndef RENDERFACTORY_H
#define RENDERFACTORY_H

#include <QWidget>

class RenderArea;

class RenderFactory
{
public:
    virtual ~RenderFactory() {}
    virtual RenderArea *makeRenderArea(QWidget *parent, int z, int one_side_length) = 0;

protected:
    RenderFactory() {}
};

#endif // RENDERFACTORY_H
