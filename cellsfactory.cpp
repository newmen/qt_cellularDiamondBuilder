#include "cellsfactory.h"
#include "cellular.h"

CellsFactory::~CellsFactory()  {
    if (_single_cellular) delete _single_cellular;
}

Cellular *CellsFactory::makeCellular() {
   if (!_single_cellular) {
       _single_cellular = new Cellular(this, _cellular_num_x, _cellular_num_y);
   }
   return _single_cellular;
}
