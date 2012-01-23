#ifndef RENDERAREAI_H
#define RENDERAREAI_H

#include "cellulario.h"

class RenderAreaI : public CellularIO
{
public:
    void moveZ(int z) { _curr_z = z; }

protected:
    RenderAreaI(Cellular *cellular) : CellularIO(cellular), _curr_z(0) {}

    int currZ() const { return _curr_z; }

private:
    RenderAreaI(const RenderAreaI &);
    RenderAreaI &operator= (const RenderAreaI &);

    int _curr_z;
};

#endif // RENDERAREAI_H
