#ifndef DIMERROW_H
#define DIMERROW_H

#include <list>
#include <utility>

template<class SimpleCellType>
class DimerRow
{
public:
    typedef std::pair<SimpleCellType*, SimpleCellType*> Dimer;
    typedef std::list<Dimer> Dimers;

    struct RowsSorter
    {
        bool operator() (const DimerRow<SimpleCellType> *dr1, const DimerRow<SimpleCellType> *dr2) const {
            return dr1->length() > dr2->length();
        }
    };

    DimerRow(int vertical_index, int horizontal_index, SimpleCellType *first_cell, SimpleCellType *second_cell);

    void addDimer(SimpleCellType *first_cell, SimpleCellType *second_cell);

    int length() const { return _dimers.size(); }

    bool isBeginningRow() const { return _horizontal_index == 0; }
    int verticalIndex() const { return _vertial_index; }

    bool near(int horizontal_index) const;
    bool cover(const DimerRow<SimpleCellType> *other) const;
    bool intercept(const DimerRow<SimpleCellType> *other) const;

    void expandTail(DimerRow<SimpleCellType> *other);
    void truncate(const DimerRow<SimpleCellType> *largest_row);

    void apply();

private:
    DimerRow();

    int leftLimitIndex() const { return _horizontal_index + length(); }

    Dimers _dimers;
    int _vertial_index, _horizontal_index;
    int _tail_length;
};

#endif // DIMERROW_H
