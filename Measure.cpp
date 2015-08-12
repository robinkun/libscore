#include "Measure.h"

Measure::Measure() {
    _prev = nullptr;
    _next = nullptr;
    _first = nullptr;
    _last = nullptr;
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
    if(_last == nullptr) {
        _last = n;
        _first = n;
        _last->setPrev(nullptr);
        _first->setNext(nullptr);
    }
    else {
        _last->setNext(n);
        _last->next()->setPrev(_last);
        _last = _last->next();
        _last->setNext(nullptr);
    }
}

/*--------------------------------------------
 * リストのpush_front
--------------------------------------------*/
void Measure::push_front(Note* n) {
    _size++;
    if(_first == nullptr) {
        _last = n;
        _first = n;
        _last->setPrev(nullptr);
        _first->setNext(nullptr);
    }
    else {
        _first->setPrev(n);
        _first->prev()->setNext(_first);
        _first = _first->prev();
        _first->setPrev(nullptr);
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
