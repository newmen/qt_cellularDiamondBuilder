#include "hydrocarbon.h"
#include <cstdlib>

HydroCarbon::HydroCarbon(const char* spec) : _actives(0), _hydrogens(0) {
    for (const char* pc = spec; *pc; ++pc) {
        if (*pc == '*') ++_actives;
        else if (*pc == 'H') {
            ++pc;
            if (*pc) _hydrogens = atoi(pc);
            else {
                _hydrogens = 1;
                break;
            }
        }
    }
}
