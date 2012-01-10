#include "dimerrow.h"

DimerRow::DimerRow(int vertical_index, int horizontal_index, SimpleCell *first_cell, SimpleCell *second_cell)
    : _vertial_index(vertical_index), _horizontal_index(horizontal_index), _tail_length(0)
{
    addDimer(first_cell, second_cell);
}

void DimerRow::addDimer(SimpleCell *first_cell, SimpleCell *second_cell) {
    _dimers.push_back(Dimer(first_cell, second_cell));
}

bool DimerRow::near(int horizontal_index) const {
    return leftLimitIndex() == horizontal_index;
}

bool DimerRow::cover(const DimerRow *other) const {
    if (_horizontal_index <= other->_horizontal_index) {
        return other->leftLimitIndex() <= leftLimitIndex();
    }
    if (_tail_length > 0) {
        return other->_horizontal_index < _tail_length && other->leftLimitIndex() <= _tail_length;
    }
    return false;
}

bool DimerRow::intercept(const DimerRow *other) const {
    if (other->_horizontal_index > _horizontal_index) {                                         // магические числа (см. бумажку)
        return other->_horizontal_index < leftLimitIndex() ||                                   // 2, 3, 10, 11
                (other->_tail_length > 0 && _horizontal_index < other->_tail_length);           // 9, 10, 11
    } else if (other->_horizontal_index < _horizontal_index) {
        return _horizontal_index < other->leftLimitIndex() ||                                   // 1, 4, 8, 12
                (_tail_length > 0 && other->_horizontal_index < _tail_length);                  // 5, 8, 12
    }
    return false;
}

void DimerRow::expandTail(DimerRow *other) {
    _tail_length = other->length();
    _dimers.splice(_dimers.end(), other->_dimers);
}

void DimerRow::truncate(const DimerRow *largest_row) {                                          // магия чисел соответствует,
    if (_horizontal_index > largest_row->_horizontal_index) {                                   // только тут вызов наоборот!
        if (_horizontal_index < largest_row->leftLimitIndex()) {                                // 2, 3, 10, 11
            Dimers::iterator cut_end = _dimers.begin();
            advance(cut_end, largest_row->leftLimitIndex() - _horizontal_index);
            _dimers.erase(_dimers.begin(), cut_end);
            if (length() <= _tail_length) {                                                     // 2, 10, 11
                _horizontal_index = _tail_length - length();
                _tail_length = 0;
            } else {                                                                            // 3
                _horizontal_index = largest_row->leftLimitIndex();
            }
        }
        if (_tail_length > 0 && largest_row->_horizontal_index < _tail_length) {                // 9
            Dimers::iterator cut_begin = _dimers.begin();
            int distance = _tail_length - largest_row->_horizontal_index;
            advance(cut_begin, length() - distance);
            _dimers.erase(cut_begin, _dimers.end());
            _tail_length -= distance;
        }
    }
    if (_horizontal_index < largest_row->_horizontal_index) {
        if (largest_row->_horizontal_index < leftLimitIndex()) {                                // 1, 4, 8, 12
            Dimers::iterator cut_begin = _dimers.begin();
            int distance = largest_row->_horizontal_index - _horizontal_index;
            advance(cut_begin, distance);
            _dimers.erase(cut_begin, _dimers.end());
            if (_tail_length > 0) {                                                             // 12
                _tail_length -= distance;
                if (_tail_length < 0) _tail_length = 0;
            }
        }
        if (largest_row->_tail_length > 0 && _horizontal_index < largest_row->_tail_length) {   // 5, 8, 12
            Dimers::iterator cut_end = _dimers.begin();
            int distance = largest_row->_tail_length - _horizontal_index;
            advance(cut_end, distance);
            _dimers.erase(_dimers.begin(), cut_end);
            _horizontal_index += distance;
        }
    }
}

void DimerRow::apply(ComplexCell::Part part) {
    for (Dimers::iterator p = _dimers.begin(); p != _dimers.end(); ++p) {
        p->first->setDimerDirection((part == ComplexCell::DOWN) ? SimpleCell::DOWN : SimpleCell::RIGHT);
        p->second->setDimerDirection((part == ComplexCell::DOWN) ? SimpleCell::UP : SimpleCell::LEFT);
    }
}
