#ifndef HYDROCARBON_H
#define HYDROCARBON_H

class HydroCarbon
{
public:
    HydroCarbon(const char* spec);

private:
    HydroCarbon();
    HydroCarbon(const HydroCarbon &);
    HydroCarbon &operator= (const HydroCarbon &);

    int _actives, _hydrogens;
};

#endif // HYDROCARBON_H
