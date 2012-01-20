#ifndef SINGLECELLULARFACTORY_H
#define SINGLECELLULARFACTORY_H

class Cellular;

class SingleCellularFactory
{
public:
    virtual ~SingleCellularFactory() {}
    virtual Cellular *cellularInstance() = 0;

protected:
    SingleCellularFactory() {}
};

#endif // SINGLECELLULARFACTORY_H
