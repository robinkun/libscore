/*--------------------------------------------
 * 小節を表すクラス
--------------------------------------------*/
#ifndef MEASURE_H
#define MEASURE_H

#include "Note.h"

class Measure {
    Measure* _prev;
    Measure* _next;
    Note* _first;
    Note* _last;
    boost::rational<int> _time;
    int _size;
    int _tick;
public:
    Measure();
    ~Measure();
    Measure* prev() const           {return _prev;}
    void setPrev(Measure* m)        {_prev = m;}
    Measure* next() const           {return _next;}
    void setNext(Measure* m)        {_next = m;}
    int tick()                      {return _tick;}
    void setTick(int t)             {_tick = t;}
    boost::rational<int> time()          {return _time;}
    void setTime(boost::rational<int> t) {_time = t;}

    Note* first()                   {return _first;}
    Note* last()                    {return _last;}
    int size() const                {return _size;}
    void push_back(Note*);
    void push_front(Note*);
    void pop_back();
    void pop_front();
};

#endif // MEASURE_H
