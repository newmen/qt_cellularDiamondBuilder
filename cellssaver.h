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
    CellsSaver(const CellsSaver &);
    CellsSaver &operator= (const CellsSaver &);

    bool isEmpty(ComplexCell &cell);

    std::ofstream &_file;
};

#endif // CELLSSAVER_H
