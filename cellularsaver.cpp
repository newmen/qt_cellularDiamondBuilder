#include "cellularsaver.h"
#include "savefileerror.h"
#include "cellssaver.h"

CellularSaver::CellularSaver(Cellular *cellular, const std::string &file_name)
    : CellularIO(cellular), _file(file_name.c_str())
{
    if (!_file) throw SaveFileError(file_name);

    _file << cellular->dimX() << ' ' << cellular->dimY() << ' ' << cellular->dimZ() << '\n';
}

CellsVisitor *CellularSaver::createVisitor() {
    return new CellsSaver(_file);
}

void CellularSaver::save() {
    _file << "+\n";

    CellsVisitor *cells_saver = createVisitor();
    cellular()->store(cells_saver);
    delete cells_saver;
}
