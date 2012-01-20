#include "cellsfactory.h"
#include "cellular.h"

CellsFactory::~CellsFactory()  {
    if (_single_cellular) delete _single_cellular;
}

Cellular *CellsFactory::cellularInstance() {
   if (!_single_cellular) {
       _single_cellular = new Cellular(this, _cellular_dims.x, _cellular_dims.y, _cellular_dims.z);
   }
   return _single_cellular;
}
