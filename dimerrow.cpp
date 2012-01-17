#include "dimerrow.h"

template<class SimpleCellType>
DimerRow<SimpleCellType>::DimerRow(int vertical_index, int horizontal_index, SimpleCellType *first_cell, SimpleCellType *second_cell)
    : _vertial_index(vertical_index), _horizontal_index(horizontal_index), _tail_length(0)
{
    addDimer(first_cell, second_cell);
}

template<class SimpleCellType>
void DimerRow<SimpleCellType>::addDimer(SimpleCellType *first_cell, SimpleCellType *second_cell) {
    _dimers.push_back(Dimer(first_cell, second_cell));
}

template<class SimpleCellType>
bool DimerRow<SimpleCellType>::near(int horizontal_index) const {
    return leftLimitIndex() == horizontal_index;
}

template<class SimpleCellType>
bool DimerRow<SimpleCellType>::cover(const DimerRow<SimpleCellType> *other) const {
    if (_horizontal_index <= other->_horizontal_index) {
        return other->leftLimitIndex() <= leftLimitIndex();
    }
    if (_tail_length > 0) {
        return other->_horizontal_index < _tail_length && other->leftLimitIndex() <= _tail_length;
    }
    return false;
}

template<class SimpleCellType>
bool DimerRow<SimpleCellType>::intercept(const DimerRow<SimpleCellType> *other) const {
    if (other->_horizontal_index > _horizontal_index) {                                         // магические числа (см. бумажку)
        return other->_horizontal_index < leftLimitIndex() ||                                   // 2, 3, 10, 11
                (other->_tail_length > 0 && _horizontal_index < other->_tail_length);           // 9, 10, 11
    } else if (other->_horizontal_index < _horizontal_index) {
        return _horizontal_index < other->leftLimitIndex() ||                                   // 1, 4, 8, 12
                (_tail_length > 0 && other->_horizontal_index < _tail_length);                  // 5, 8, 12
    }
    return false;
}

template<class SimpleCellType>
void DimerRow<SimpleCellType>::expandTail(DimerRow<SimpleCellType> *other) {
    _tail_length = other->length();
    _dimers.splice(_dimers.end(), other->_dimers);
}

template<class SimpleCellType>
void DimerRow<SimpleCellType>::truncate(const DimerRow<SimpleCellType> *largest_row) {          // магия чисел соответствует,
    if (_horizontal_index > largest_row->_horizontal_index) {                                   // только тут вызов наоборот!
        if (_horizontal_index < largest_row->leftLimitIndex()) {                                // 2, 3, 10, 11
            typename Dimers::iterator cut_end = _dimers.begin();
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
            typename Dimers::iterator cut_begin = _dimers.begin();
            int distance = _tail_length - largest_row->_horizontal_index;
            advance(cut_begin, length() - distance);
            _dimers.erase(cut_begin, _dimers.end());
            _tail_length -= distance;
        }
    }
    if (_horizontal_index < largest_row->_horizontal_index) {
        if (largest_row->_horizontal_index < leftLimitIndex()) {                                // 1, 4, 8, 12
            typename Dimers::iterator cut_begin = _dimers.begin();
            int distance = largest_row->_horizontal_index - _horizontal_index;
            advance(cut_begin, distance);
            _dimers.erase(cut_begin, _dimers.end());
            if (_tail_length > 0) {                                                             // 12
                _tail_length -= distance;
                if (_tail_length < 0) _tail_length = 0;
            }
        }
        if (largest_row->_tail_length > 0 && _horizontal_index < largest_row->_tail_length) {   // 5, 8, 12
            typename Dimers::iterator cut_end = _dimers.begin();
            int distance = largest_row->_tail_length - _horizontal_index;
            advance(cut_end, distance);
            _dimers.erase(_dimers.begin(), cut_end);
            _horizontal_index += distance;
        }
    }
}

template<class SimpleCellType>
void DimerRow<SimpleCellType>::apply() {
    for (typename Dimers::iterator p = _dimers.begin(); p != _dimers.end(); ++p) {
        p->first->setDimerDirection(SimpleCellType::BACK);
        p->second->setDimerDirection(SimpleCellType::FIRST);
    }
}
