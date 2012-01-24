#ifndef HASCELLULAR_H
#define HASCELLULAR_H

#include "cellular.h"

class HasCellular
{
public:
    virtual ~HasCellular() {}

protected:
    HasCellular(Cellular *cellular) : _cellular(cellular) {}

    Cellular *cellular() { return _cellular; }
    Cellular *cellular() const { return _cellular; }

private:
    HasCellular(const HasCellular &);
    HasCellular &operator= (const HasCellular &);

    Cellular *_cellular;
};

#endif // HASCELLULAR_H
