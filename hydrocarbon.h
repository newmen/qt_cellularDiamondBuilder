#ifndef HYDROCARBON_H
#define HYDROCARBON_H

class HydroCarbon
{
public:
    HydroCarbon(const char* spec);

private:
    HydroCarbon();

    int _actives, _hydrogens;
};

#endif // HYDROCARBON_H
