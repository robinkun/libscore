/*--------------------------------------------
 * 小節を表すクラス
--------------------------------------------*/
#ifndef MEASURE_H
#define MEASURE_H

#include "Note.h"
#include <list>

class Tempo {
  int _bpm;
  boost::rational<int> _pos;

  void setBPM(int b)                  {_bpm = b;}
  int bpm()                           {return _bpm;}
  boost::rational<int> pos()          {return _pos;}
  void setPos(boost::rational<int> p) {_pos = p;}
  void setPos(int n, int d)           {_pos = boost::rational<int>(n, d);}
};

class Measure {
    Measure* _prev;
    Measure* _next;
    Note _end;
    Note* _front;
    Note* _back;
    boost::rational<int> _time;
    std::list<Tempo> _tempo;
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

    Note* front()                   {return _front;}
    Note* back()                    {return _back;}
    int size() const                {return _size;}
    void push_back(Note*);
    void push_front(Note*);
    void pop_back();
    void pop_front();
    Note* begin()                   {return _front;}
    Note* end()                     {return &_end;}
    bool isEmpty()                  {return _size <= 0;}
};

#endif // MEASURE_H
