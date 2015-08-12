#include "MeasureList.h"

MeasureList::MeasureList() {
    _size = 0;
    _first = nullptr;
    _last = nullptr;
}

/*--------------------------------------------
 * デストラクタ
--------------------------------------------*/
MeasureList::~MeasureList() {
    Measure* i = _first;
    Measure* tmp = _first;

    while(i != nullptr) {
        tmp = i->next();
        delete i;
        i = tmp;
    }
}

/*--------------------------------------------
 * リストのpush_back
--------------------------------------------*/
void MeasureList::push_back(Measure* m) {
    _size++;
    if(_last == nullptr) {
        _last = m;
        _first = m;
        _last->setPrev(nullptr);
        _first->setNext(nullptr);
    }
    else {
        _last->setNext(m);
        _last->next()->setPrev(_last);
        _last = _last->next();
        _last->setNext(nullptr);
    }
}

/*--------------------------------------------
 * リストのpush_front
--------------------------------------------*/
void MeasureList::push_front(Measure* m) {
    _size++;
    if(_first == nullptr) {
        _last = m;
        _first = m;
        _last->setPrev(nullptr);
        _first->setNext(nullptr);
    }
    else {
        _first->setPrev(m);
        _first->prev()->setNext(_first);
        _first = _first->prev();
        _first->setPrev(nullptr);
    }
}

/*--------------------------------------------
 * リストのpop_back
--------------------------------------------*/
void MeasureList::pop_back() {
    if(_first == nullptr) {
        return;
    } else {
        _first = _first->next();
        if(_first != _last) {
            delete _first->prev();
        }
        _first->setPrev(nullptr);
        _size--;
    }
}

/*--------------------------------------------
 * リストのpop_front
--------------------------------------------*/
void MeasureList::pop_front() {
    if(_last == nullptr) {
        return;
    } else {
        _last = _last->prev();
        if(_last != _first) {
            delete _last->next();
        }
        _last->setNext(nullptr);
        _size--;
    }
}

