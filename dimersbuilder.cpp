#include "dimersbuilder.h"
#include <algorithm>
#include <cstdlib>
//#include <iostream>

DimersBuilder::~DimersBuilder() {
    deleteFormedRows();
}

void DimersBuilder::reset(int max_vertical_index, int max_horizontal_index) {
    deleteFormedRows();

    _max_vertical_index = max_vertical_index;
    _max_horizontal_index = max_horizontal_index;

    _rows_plane.clear();
    _all_rows.clear();
    _formed_rows.clear();
}

void DimersBuilder::addDimer(int vertical_index, int horizontal_index, SimpleCell *first_cell, SimpleCell *second_cell) {
    typename RowsPlane::iterator find_result = _rows_plane.find(vertical_index);
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

typename DimersBuilder::DimerRows *DimersBuilder::formedRows() {
//    std::cout << "------------------------" << std::endl;
//    std::cout << "_all_rows.size() = " << _all_rows.size() << std::endl;

    shiftLargestRow();

//    std::cout << "_real_rows.size() = " << _real_rows.size() << std::endl;
    return &_formed_rows;
}

void DimersBuilder::deleteFormedRows() {
    for (typename DimerRows::iterator p = _formed_rows.begin(); p != _formed_rows.end(); ++p) {
        delete *p;
    }
}

void DimersBuilder::buildRow(int vertical_index, int horizontal_index, SimpleCell *first_cell, SimpleCell *second_cell) {
    DimerRow *new_row = new DimerRow(vertical_index, horizontal_index, first_cell, second_cell);
    _rows_plane[vertical_index].push_back(new_row);
    _all_rows.push_back(new_row);
}

void DimersBuilder::destroyRow(DimerRow *row) {
    _all_rows.erase(find(_all_rows.begin(), _all_rows.end(), row));
    delete row;
}

void DimersBuilder::shiftLargestRow() {
//    std::cout << "shift [" << _all_rows.size() << "]" << std::endl;
    if (_all_rows.empty()) return;
    typename DimerRow::Sorter sorter;
    _all_rows.sort(sorter);

    int num_of_same_length = 1;
    typename DimerRows::iterator prev_dr = _all_rows.begin();
    typename DimerRows::iterator curr_dr = _all_rows.begin();
    advance(curr_dr, 1);
    for (; curr_dr != _all_rows.end(); ++prev_dr, ++curr_dr) {
        if ((*prev_dr)->length() != (*curr_dr)->length()) break;
        ++num_of_same_length;
    }

//    std::cout << "nums of same length = " << num_of_same_length << std::endl;
    typename DimerRows::iterator i_largest_row = _all_rows.begin();
    advance(i_largest_row, rand() % num_of_same_length);

    _formed_rows.push_back(*i_largest_row);
    _all_rows.erase(i_largest_row);

    int vertical_index = (*i_largest_row)->verticalIndex();
    truncateRows(vertical_index - 1, *i_largest_row);
    truncateRows(vertical_index + 1, *i_largest_row);

    shiftLargestRow();
}

void DimersBuilder::truncateRows(int vertical_index, const DimerRow *largest_row) {
    if (vertical_index > _max_vertical_index) vertical_index = 0;
    else if (vertical_index < 0) vertical_index = _max_vertical_index;

    typename RowsPlane::iterator find_result = _rows_plane.find(vertical_index);
    if (find_result == _rows_plane.end()) return;

    typename DimerRows::iterator p_dimer_row = find_result->second.begin();
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
