/*--------------------------------------------
 * 楽譜の音符を表すクラス
--------------------------------------------*/
#ifndef NOTE_H
#define NOTE_H
#include <boost/rational.hpp>

class Note {
    int _pitch;
    boost::rational<int> _length;
    boost::rational<int> _pos;
    int _finger;
    Note* _next;
    Note* _prev;

public:
    Note();
    int pitch() const                   {return _pitch;}
    void setPitch(int p)                {_pitch = p;}
    boost::rational<int> length()            {return _length;}
    void setLength(boost::rational<int> l)   {_length = l;}
    void setLength(int n, int d)        {_length = boost::rational<int>(n, d);}
    boost::rational<int> pos()          {return _pos;}
    void setPos(boost::rational<int> p) {_pos = p;}
    void setPos(int n, int d)           {_pos = boost::rational<int>(n, d);}
    int finger() const                  {return _finger;}
    void setFinger(int f)               {_finger = f;}
    Note* prev() const                  {return _prev;}
    void setPrev(Note* n)               {_prev = n;}
    Note* next() const                  {return _next;}
    void setNext(Note* n)               {_next = n;}
};

#endif // NOTE_H
