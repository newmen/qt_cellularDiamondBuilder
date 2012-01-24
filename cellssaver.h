#ifndef CELLSSAVER_H
#define CELLSSAVER_H

#include <fstream>
#include "cellsvisitor.h"

class CellsSaver : public CellsVisitor
{
public:
    CellsSaver(std::ofstream &file) : _file(file) {}

    void visitComplexCell(ComplexCell &cell);
    void visitSimpleCell(SimpleCell &cell);

private:
    bool isEmpty(ComplexCell &cell);

    std::ofstream &_file;
};

#endif // CELLSSAVER_H
