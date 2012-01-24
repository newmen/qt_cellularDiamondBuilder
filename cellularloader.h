#ifndef CELLULARLOADER_H
#define CELLULARLOADER_H

#include <string>
#include <fstream>
#include "hascellular.h"

class CellularLoader : public HasCellular
{
public:
    CellularLoader(Cellular *cellular, const std::string &file_name);

    void load();

private:
    CellularLoader(const CellularLoader &);
    CellularLoader &operator= (const CellularLoader &);

    std::ifstream _file;
};

#endif // CELLULARLOADER_H
