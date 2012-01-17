#ifndef CELLSITERATOR_H
#define CELLSITERATOR_H

class IteratorOutOfBounds {};

template<class CellType>
class CellsIterator
{
public:
    virtual void next();
    virtual bool isDone() const;
    virtual CellType *current() const;

protected:
    CellsIterator() {}
};

#endif // CELLSITERATOR_H
