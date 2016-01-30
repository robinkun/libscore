#include "MeasureList.h"

MeasureList::MeasureList() {
    _size = 0;
    _first = &_begin;
    _last = &_end;
    _begin.setPrev(nullptr);
    _end.setNext(nullptr);
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
    if(_last == &_end) {
        _last = m;
        _first = m;
        _last->setPrev(&_begin);
        _first->setNext(&_end);
    }
    else {
        _last->setNext(m);
        _last->next()->setPrev(_last);
        _last = _last->next();
        _last->setNext(&_end);
        _end.setPrev(_last);
    }
}

/*--------------------------------------------
 * リストのpush_front
--------------------------------------------*/
void MeasureList::push_front(Measure* m) {
    _size++;
    if(_first == &_begin) {
        _last = m;
        _first = m;
        _last->setPrev(&_begin);
        _first->setNext(&_end);
    }
    else {
        _first->setPrev(m);
        _first->prev()->setNext(_first);
        _first = _first->prev();
        _first->setPrev(&_begin);
        _begin.setNext(_first);
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

