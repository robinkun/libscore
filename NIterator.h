/*--------------------------------------------
 * Noteクラスのリストに使えるイテレータ
--------------------------------------------*/
#ifndef NITERATOR_H
#define NITERATOR_H

#include "Note.h"

class NIterator {
    Note* note;
public:
    NIterator(Note* n) {note = n;}
    NIterator() {}
    Note* operator->();
    Note* operator++(int);
    Note* operator--(int);
    Note* operator*();
    NIterator operator=(Note* m);
    operator Note*();
};

#endif // NITERATOR_H
