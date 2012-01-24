#include "cellularloader.h"
#include "loadfileerror.h"
#include "complexcell.h"
#include "simplecell.h"
#include "common.h"

CellularLoader::CellularLoader(Cellular *cellular, const std::string &file_name)
    : HasCellular(cellular), _file(file_name.c_str())
{
    if (!_file) throw LoadFileError(file_name);
}

void CellularLoader::load() {
    dim3 cellular_dims;
    _file >> cellular_dims.x  >> cellular_dims.y >> cellular_dims.z;
    cellular()->resize(cellular_dims);

    char separator;
    _file >> separator;

    ComplexCell *complex_cell;
    int3 complex_coords;
    int simple_state;
    while (true) {
        _file >> complex_coords.x >> complex_coords.y >> complex_coords.z;
        if (_file.eof()) break;

        complex_cell = cellular()->cell(complex_coords.x, complex_coords.y, complex_coords.z);
        for (int y = 0; y < 2; ++y) {
            for (int x = 0; x < 2; ++x) {
                _file >> simple_state;
                complex_cell->cell(x, y)->setState(simple_state);
            }
        }
    }
}
