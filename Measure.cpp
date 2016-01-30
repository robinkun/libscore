#include "Measure.h"

Measure::Measure() {
    _prev = nullptr;
    _next = nullptr;
    _first = &_begin;
    _last = &_end;
    _begin.setPrev(nullptr);
    _end.setNext(nullptr);
    _time = 1;
}

Measure::~Measure() {
    Note* i = _first;
    Note* tmp = _first;

    // メモリ解放ループ
    while(i != nullptr) {
        tmp = i->next();
        delete i;
        i = tmp;
    }
}

/*--------------------------------------------
 * リストのpush_back
--------------------------------------------*/
void Measure::push_back(Note* n) {
    _size++;
    if(_last == &_end) {
        _last = n;
        _first = n;
        _last->setPrev(&_begin);
        _first->setNext(&_end);
    }
    else {
        _last->setNext(n);
        _last->next()->setPrev(_last);
        _last = _last->next();
        _last->setNext(&_end);
        _end.setPrev(_last);
    }
}

/*--------------------------------------------
 * リストのpush_front
--------------------------------------------*/
void Measure::push_front(Note* n) {
    _size++;
    if(_first == &_begin) {
        _last = n;
        _first = n;
        _last->setPrev(&_begin);
        _first->setNext(&_end);
    }
    else {
        _first->setPrev(n);
        _first->prev()->setNext(_first);
        _first = _first->prev();
        _first->setPrev(&_begin);
        _begin.setNext(_first);
    }
}

/*--------------------------------------------
 * リストのpop_back
--------------------------------------------*/
void Measure::pop_back() {
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
void Measure::pop_front() {
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
