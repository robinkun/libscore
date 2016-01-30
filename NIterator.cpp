#include "NIterator.h"

/*--------------------------------------------
 * 演算子->のオーバーロード
 * イテレータが指すポインタの中身に
 * アクセスしたいときに使う
--------------------------------------------*/
Note* NIterator::operator->() {
    if(note == nullptr) {
        puts("null pointer");
        exit(1);
    }
    return note;
}

/*--------------------------------------------
 * 演算子++のオーバーロード
 * イテレータが指すポインタをリストの次の要素に移す
--------------------------------------------*/
Note* NIterator::operator++(int) {
    if(note == nullptr) {
        puts("null pointer");
        exit(1);
    }
    Note* old = note;
    note = note->next();
    return old;
}

/*--------------------------------------------
 * 演算子++のオーバーロード
 * イテレータが指すポインタをリストの前の要素に移す
--------------------------------------------*/
Note* NIterator::operator--(int) {
    if(note == nullptr) {
        puts("null pointer");
        exit(1);
    }
    Note* old = note;
    note = note->prev();
    return old;
}

Note* NIterator::operator*() {
    return note;
}

/*--------------------------------------------
 * 演算子=のオーバーロード
 * イテレータが指すポインタをmに変える
--------------------------------------------*/
NIterator NIterator::operator=(Note* n) {
    note = n;
    return *this;
}

/*--------------------------------------------
 * Note* = NIteratorとしたときに、
 * Noteのポインタが返されるようにする
--------------------------------------------*/
NIterator::operator Note*() {
    return note;
}

