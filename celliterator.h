#ifndef CELLITERATOR_H
#define CELLITERATOR_H

class IteratorOutOfBounds {};

template<class CellType>
class CellIterator
{
public:
    virtual void next();
    virtual bool isDone() const;
    virtual CellType *current() const;

protected:
    CellIterator() {}
};

#endif // CELLITERATOR_H
