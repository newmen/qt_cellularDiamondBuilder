#include "dimerrowsplanebuilder.h"
#include <algorithm>
//#include <iostream>

DimerRowsPlaneBuilder::DimerRowsPlaneBuilder(int max_vertical_index, int max_horizontal_index)
    : _max_vertical_index(max_vertical_index), _max_horizontal_index(max_horizontal_index) { }

DimerRowsPlaneBuilder::~DimerRowsPlaneBuilder() {
    for (DimerRows::iterator p = _real_rows.begin(); p != _real_rows.end(); ++p) {
        delete *p;
    }
}

void DimerRowsPlaneBuilder::addDimer(int vertical_index, int horizontal_index, SimpleCell *first_cell, SimpleCell *second_cell) {
    RowsPlane::iterator find_result = _rows_plane.find(vertical_index);
    if (find_result != _rows_plane.end()) {
        DimerRow *back_row = find_result->second.back();

        if (back_row->near(horizontal_index)) {
            back_row->addDimer(first_cell, second_cell);
        } else {
            buildRow(vertical_index, horizontal_index, first_cell, second_cell);
            back_row = find_result->second.back();
        }

        // TODO в предыдущем else идёт лишнее выделение ресурсов, если затем димер оказывается частью начального
        if (horizontal_index == _max_horizontal_index) {
            DimerRow *front_row = find_result->second.front();
            if (front_row->isBeginningRow() && front_row != back_row) {
                back_row->expandTail(front_row);
                find_result->second.pop_front();
                destroyRow(front_row);
            }
        }
    } else {
        buildRow(vertical_index, horizontal_index, first_cell, second_cell);
    }
}

void DimerRowsPlaneBuilder::formRows() {
//    std::cout << "------------------------" << std::endl;
//    std::cout << "_all_rows.size() = " << _all_rows.size() << std::endl;

    shiftLargestRow();

//    std::cout << "_real_rows.size() = " << _real_rows.size() << std::endl;
    for (DimerRows::iterator dr = _real_rows.begin(); dr != _real_rows.end(); ++dr) {
        (*dr)->apply();
    }
}

void DimerRowsPlaneBuilder::buildRow(int vertical_index, int horizontal_index, SimpleCell *first_cell, SimpleCell *second_cell) {
    DimerRow *new_row = new DimerRow(vertical_index, horizontal_index, first_cell, second_cell);
    _rows_plane[vertical_index].push_back(new_row);
    _all_rows.push_back(new_row);
}

void DimerRowsPlaneBuilder::destroyRow(DimerRow *row) {
    _all_rows.erase(find(_all_rows.begin(), _all_rows.end(), row));
    delete row;
}

void DimerRowsPlaneBuilder::shiftLargestRow() {
//    std::cout << "shift [" << _all_rows.size() << "]" << std::endl;
    if (_all_rows.empty()) return;

    _all_rows.sort(RowsSorter());

    DimerRow *largest_row = *(_all_rows.begin());
    _real_rows.push_back(largest_row);
    _all_rows.pop_front();

    int vertical_index = largest_row->verticalIndex();
    truncateRows(vertical_index - 1, largest_row);
    truncateRows(vertical_index + 1, largest_row);

    shiftLargestRow();
}

void DimerRowsPlaneBuilder::truncateRows(int vertical_index, const DimerRow *largest_row) {
    if (vertical_index > _max_vertical_index) vertical_index = 0;
    else if (vertical_index < 0) vertical_index = _max_vertical_index;

    RowsPlane::iterator find_result = _rows_plane.find(vertical_index);
    if (find_result == _rows_plane.end()) return;

    DimerRows::iterator p_dimer_row = find_result->second.begin();
    while (p_dimer_row != find_result->second.end()) {
        DimerRow *curr_row = *p_dimer_row;
        if (largest_row->cover(curr_row)) {
            p_dimer_row = find_result->second.erase(p_dimer_row);
            destroyRow(curr_row);
        } else {
            if (largest_row->intercept(curr_row)) {
                curr_row->truncate(largest_row);
            }
            ++p_dimer_row;
        }
    }
}
