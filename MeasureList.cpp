#include "MeasureList.h"

MeasureList::MeasureList() {
    _size = 0;
    _front = &_end;
    _back = &_end;
    _end.setPrev(&_end); // 果たしてこれは正しいのだろうか
    _end.setNext(&_end);
}

/*--------------------------------------------
 * デストラクタ
--------------------------------------------*/
MeasureList::~MeasureList() {
    Measure* i = _front;
    Measure* tmp = _front;

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
    if(_back == &_end) {
        _back = m;
        _front = m;
        _back->setPrev(&_end);
        _front->setNext(&_end);
    }
    else {
        _back->setNext(m);
        _back->next()->setPrev(_back);
        _back = _back->next();
        _back->setNext(&_end);
        _end.setPrev(_back);
    }
}

/*--------------------------------------------
 * リストのpush_front
--------------------------------------------*/
void MeasureList::push_front(Measure* m) {
    _size++;
    if(_front == &_end) {
        _back = m;
        _front = m;
        _back->setPrev(&_end);
        _front->setNext(&_end);
    }
    else {
        _front->setPrev(m);
        _front->prev()->setNext(_front);
        _front = _front->prev();
        _front->setPrev(&_end);
        _end.setNext(_front);
    }
}

/*--------------------------------------------
 * リストのpop_back
--------------------------------------------*/
void MeasureList::pop_back() {
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
void MeasureList::pop_front() {
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

