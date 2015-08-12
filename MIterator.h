/*--------------------------------------------
 * Measureクラスのリストに使えるイテレータ
--------------------------------------------*/
#ifndef MITERATOR_H
#define MITERATOR_H

#include "Measure.h"

class MIterator {
    Measure* measure;
public:
    MIterator(Measure* m) {measure = m;}
    MIterator() {}
    Measure* operator->();
    Measure* operator++(int);
    Measure* operator--(int);
    Measure* operator*();
    MIterator operator=(Measure* m);
    operator Measure*();
    bool isEnd();
};

#endif // MITERATOR_H
