/*--------------------------------------------
 * 小節の集まりを表すリスト
--------------------------------------------*/
#ifndef MEASURELIST_H
#define MEASURELIST_H

#include "Measure.h"
#include "MIterator.h"

class MeasureList {
    int _size;
    Measure* _front;
    Measure* _back;
    Measure _end;
public:
    MeasureList();
    ~MeasureList();
    int size() const                {return _size;}
    void push_back(Measure*);
    void push_front(Measure*);
    void pop_back();
    void pop_front();
    Measure* front()                {return _front;}
    Measure* back()                 {return _back;}
    Measure* begin()                {return _front;}
    Measure* end()                  {return &_end;}
    bool isEmpty()                  {return _size <= 0;}
};

#endif // MEASURELIST_H
