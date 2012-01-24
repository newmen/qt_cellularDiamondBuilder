#ifndef CELLULARSAVER_H
#define CELLULARSAVER_H

#include <string>
#include <fstream>
#include "cellulario.h"

class CellularSaver : public CellularIO
{
public:
    CellularSaver(Cellular *cellular, const std::string &file_name);

    void save();

protected:
    CellsVisitor *createVisitor();

private:
    CellularSaver(const CellularSaver &);
    CellularSaver &operator= (const CellularSaver &);

    std::ofstream _file;
};

#endif // CELLULARSAVER_H
