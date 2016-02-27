#include "Measure.h"

Measure::Measure() {
    _prev = nullptr;
    _next = nullptr;
    _front = &_end;
    _back = &_end;
    _end.setPrev(&_end);
    _end.setNext(&_end);
    _time = 1;
    _size = 0;
}

Measure::~Measure() {
    Note* i = _front;
    Note* tmp = _front;

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
    if(_back == &_end) {
        _back = n;
        _front = n;
        _back->setPrev(&_end);
        _front->setNext(&_end);
    }
    else {
        _back->setNext(n);
        _back->next()->setPrev(_back);
        _back = _back->next();
        _back->setNext(&_end);
        _end.setPrev(_back);
    }
}

/*--------------------------------------------
 * リストのpush_front
--------------------------------------------*/
void Measure::push_front(Note* n) {
    _size++;
    if(_front == &_end) {
        _back = n;
        _front = n;
        _back->setPrev(&_end);
        _front->setNext(&_end);
    }
    else {
        _front->setPrev(n);
        _front->prev()->setNext(_front);
        _front = _front->prev();
        _front->setPrev(&_end);
        _end.setNext(_front);
    }
}

/*--------------------------------------------
 * リストのpop_back
--------------------------------------------*/
void Measure::pop_back() {
    if(_front == nullptr) {
        return;
    } else {
        _front = _front->next();
        if(_front != _back) {
            delete _front->prev();
        }
        _front->setPrev(nullptr);
        _size--;
    }
}

/*--------------------------------------------
 * リストのpop_front
--------------------------------------------*/
void Measure::pop_front() {
    if(_back == nullptr) {
        return;
    } else {
        _back = _back->prev();
        if(_back != _front) {
            delete _back->next();
        }
        _back->setNext(nullptr);
        _size--;
    }
}
