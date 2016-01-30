#include "MIterator.h"

/*--------------------------------------------
 * 演算子->のオーバーロード
 * イテレータが指すポインタの中身に
 * アクセスしたいときに使う
--------------------------------------------*/
Measure* MIterator::operator->() {
    if(measure == nullptr) {
        puts("null pointer");
        exit(1);
    }
    return measure;
}

/*--------------------------------------------
 * 演算子++のオーバーロード
 * イテレータが指すポインタをリストの次の要素に移す
--------------------------------------------*/
Measure* MIterator::operator++(int) {
    if(measure == nullptr) {
        puts("null pointer");
        exit(1);
    }
    Measure* old = measure;
    measure = measure->next();
    return old;
}

/*--------------------------------------------
 * 演算子++のオーバーロード
 * イテレータが指すポインタをリストの前の要素に移す
--------------------------------------------*/
Measure* MIterator::operator--(int) {
    if(measure == nullptr) {
        puts("null pointer");
        exit(1);
    }
    Measure* old = measure;
    measure = measure->prev();
    return old;
}

Measure* MIterator::operator*() {
    return measure;
}

/*--------------------------------------------
 * 演算子=のオーバーロード
 * イテレータが指すポインタをmに変える
--------------------------------------------*/
MIterator MIterator::operator=(Measure* m) {
    measure = m;
    return *this;
}

/*--------------------------------------------
 * Measure* = MIteratorとしたときに、
 * Measureのポインタが返されるようにする
--------------------------------------------*/
MIterator::operator Measure*() {
    return measure;
}

