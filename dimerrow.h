#ifndef DIMERROW_H
#define DIMERROW_H

#include <list>
#include <utility>
#include "simplecell.h"

class DimerRow
{
    typedef std::pair<SimpleCell*, SimpleCell*> Dimer;
    typedef std::list<Dimer> Dimers;

public:
    struct Sorter
    {
        bool operator() (const DimerRow *dr1, const DimerRow *dr2) const {
            return dr1->length() > dr2->length();
        }
    };

    DimerRow(int vertical_index, int horizontal_index, SimpleCell *first_cell, SimpleCell *second_cell);

    void addDimer(SimpleCell *first_cell, SimpleCell *second_cell);

    int length() const { return _dimers.size(); }

    bool isBeginningRow() const { return _horizontal_index == 0; }
    int verticalIndex() const { return _vertial_index; }

    bool near(int horizontal_index) const;
    bool cover(const DimerRow *other) const;
    bool intercept(const DimerRow *other) const;

    void expandTail(DimerRow *other);
    void truncate(const DimerRow *largest_row);

    void apply();

private:
    DimerRow();
    DimerRow(const DimerRow &);
    DimerRow &operator= (const DimerRow &);

    int leftLimitIndex() const { return _horizontal_index + length(); }

    Dimers _dimers;
    int _vertial_index, _horizontal_index;
    int _tail_length;
};

#endif // DIMERROW_H
