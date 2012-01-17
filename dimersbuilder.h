#ifndef DIMERSBUILDER_H
#define DIMERSBUILDER_H

#include <list>
#include <map>
#include "dimerrow.h"
#include "simplecell.h"

class DimersBuilder
{
public:
    typedef std::list<DimerRow *> DimerRows;
    typedef std::map<int, DimerRows> RowsPlane;

    virtual ~DimersBuilder();

    void reset(int max_vertical_index, int max_horizontal_index);

    void addDimer(int vertical_index, int horizontal_index, SimpleCell *first_cell, SimpleCell *second_cell);
    DimerRows *formedRows();

private:
    void deleteFormedRows();
    void buildRow(int vertical_index, int horizontal_index, SimpleCell *first_cell, SimpleCell *second_cell);
    void destroyRow(DimerRow *row);
    void shiftLargestRow();
    void truncateRows(int vertical_index, const DimerRow *largest_row);

    int _max_vertical_index, _max_horizontal_index;
    RowsPlane _rows_plane;
    DimerRows _all_rows, _formed_rows;
};

#endif // DIMERSBUILDER_H
