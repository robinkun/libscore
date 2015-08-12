/*--------------------------------------------
 * 小節の集まりを表すリスト
--------------------------------------------*/
#ifndef MEASURELIST_H
#define MEASURELIST_H

#include "Measure.h"
#include "MIterator.h"

class MeasureList {
    int _size;
    Measure* _first;
    Measure* _last;
public:
    MeasureList();
    ~MeasureList();
    int size() const                {return _size;}
    void push_back(Measure*);
    void push_front(Measure*);
    void pop_back();
    void pop_front();
    Measure* first()                {return _first;}
    Measure* last()                 {return _last;}
};

#endif // MEASURELIST_H
