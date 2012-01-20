#ifndef RENDERAREAI_H
#define RENDERAREAI_H

#include "cellular.h"

class RenderAreaI
{
public:
    virtual void moveZ(int z) { _curr_z = z; }

protected:
    RenderAreaI(Cellular *cellular, int z) : _cellular(cellular), _curr_z(z) {}

    Cellular *cellular() { return _cellular; }
    Cellular *cellular() const { return _cellular; }

    int currZ() const { return _curr_z; }

private:
    RenderAreaI(const RenderAreaI &);
    RenderAreaI operator= (const RenderAreaI &);

    Cellular *_cellular;
    int _curr_z;
};

#endif // RENDERAREAI_H
