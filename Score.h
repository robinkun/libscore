/*--------------------------------------------
 * 楽譜のデータ構造を表すクラス
 * MeasureListは小節のリスト
--------------------------------------------*/
#ifndef SCORE_H
#define SCORE_H

#include "MeasureList.h"

class MidiRead;

class Score : public MeasureList {
    boost::rational<int> _time;
    int _min_pitch;
    int _max_pitch;
public:
    Score();
    void setMinPitch(int mp) {_min_pitch = mp;}
    void setMaxPitch(int mp) {_max_pitch = mp;}

    int minPitch() {return _min_pitch;}
    int maxPitch() {return _max_pitch;}
};

#endif // SCORE_H
