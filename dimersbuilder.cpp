#include "dimersbuilder.h"
#include <algorithm>
#include <cstdlib>
//#include <iostream>

DimersBuilder::~DimersBuilder() {
    for (DimerRows::iterator p = _formed_rows.begin(); p != _formed_rows.end(); ++p) {
        delete *p;
    }
}

void DimersBuilder::reset(int max_vertical_index, int max_horizontal_index) {
    _max_vertical_index = max_vertical_index;
    _max_horizontal_index = max_horizontal_index;

    _rows_plane.clear();
    _all_rows.clear();
}

void DimersBuilder::addDimer(int vertical_index, int horizontal_index, SimpleCell *first_cell, SimpleCell *second_cell) {
    RowsPlane::iterator find_result = _rows_plane.find(vertical_index);
    if (find_result != _rows_plane.end()) {
        DimerRow *last_row = find_result->second.back();

        if (last_row->near(horizontal_index)) {
            last_row->addDimer(first_cell, second_cell);
        } else {
            last_row = buildRow(vertical_index, horizontal_index, first_cell, second_cell);
        }

        // TODO в предыдущем else идёт лишнее выделение ресурсов, если затем димер оказывается частью начального
        if (horizontal_index == _max_horizontal_index) {
            DimerRow *first_row = find_result->second.front();
            if (first_row->isBeginningRow() && first_row != last_row) {
                last_row->expandTail(first_row);
                find_result->second.pop_front();
                destroyRow(first_row);
            }
        }
    } else {
        buildRow(vertical_index, horizontal_index, first_cell, second_cell);
    }
}

void DimersBuilder::buildRows() {
//    std::cout << "------------------------" << std::endl;
//    std::cout << "_all_rows.size() = " << _all_rows.size() << std::endl;
    shiftLargestRow();
}

void DimersBuilder::apply() const {
    for (DimerRows::const_iterator dr = _formed_rows.begin(); dr != _formed_rows.end(); ++dr) {
        (*dr)->apply();
    }
}

DimersBuilder::RowsPlane::iterator DimersBuilder::findRowsInPlane(int vertical_index) {
    if (vertical_index > _max_vertical_index) vertical_index = 0;
    else if (vertical_index < 0) vertical_index = _max_vertical_index;

    return _rows_plane.find(vertical_index);
}

DimerRow *DimersBuilder::buildRow(int vertical_index, int horizontal_index, SimpleCell *first_cell, SimpleCell *second_cell) {
    DimerRow *new_row = new DimerRow(vertical_index, horizontal_index, first_cell, second_cell);
    _rows_plane[vertical_index].push_back(new_row);
    _all_rows.push_back(new_row);
    return new_row;
}

void DimersBuilder::destroyRow(DimerRow *row) {
    _all_rows.erase(find(_all_rows.begin(), _all_rows.end(), row));
    delete row;
}

// TODO требуется оптимизация, поскольку операция поиска по списку производится в цикле!
// возможно необходимо изменить порядок добавления рядов в контейнеры
// следует учесть тот факт, что каждый раз производится сортировка _all_rows
void DimersBuilder::destroyRows(int vertical_index) {
    RowsPlane::iterator find_result = findRowsInPlane(vertical_index);
    if (find_result == _rows_plane.end()) return;

    for (DimerRows::iterator dr = find_result->second.begin(); dr != find_result->second.end(); ++dr) {
        destroyRow(*dr);
    }

    _rows_plane.erase(find_result);
}

void DimersBuilder::shiftLargestRow() {
//    std::cout << "shift [" << _all_rows.size() << "]" << std::endl;
    if (_all_rows.empty()) return;
    typename DimerRow::Sorter sorter;
    _all_rows.sort(sorter);

    int num_of_same_length = 1;
    DimerRows::iterator prev_dr = _all_rows.begin();
    DimerRows::iterator curr_dr = _all_rows.begin();
    advance(curr_dr, 1);
    for (; curr_dr != _all_rows.end(); ++prev_dr, ++curr_dr) {
        if ((*prev_dr)->length() != (*curr_dr)->length()) break;
        ++num_of_same_length;
    }

//    std::cout << "nums of same length = " << num_of_same_length << std::endl;
    DimerRows::iterator i_largest_row = _all_rows.begin();
    advance(i_largest_row, rand() % num_of_same_length);

    _formed_rows.push_back(*i_largest_row);
    _all_rows.erase(i_largest_row);

    int vertical_index = (*i_largest_row)->verticalIndex();

    if (isCircledRow(*i_largest_row)) {
        destroyRows(vertical_index - 1);
        destroyRows(vertical_index + 1);
    } else {
        truncateRows(vertical_index - 1, *i_largest_row);
        truncateRows(vertical_index + 1, *i_largest_row);
    }

    shiftLargestRow();
}

void DimersBuilder::truncateRows(int vertical_index, const DimerRow *largest_row) {
    RowsPlane::iterator find_result = findRowsInPlane(vertical_index);
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

bool DimersBuilder::isCircledRow(DimerRow *row) const {
    return row->isBeginningRow() && row->length() == _max_horizontal_index + 1;
}
