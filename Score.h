/*--------------------------------------------
 * 楽譜のデータ構造を表すクラス
 * MeasureListは小節のリスト
--------------------------------------------*/
#ifndef SCORE_H
#define SCORE_H

#include "Measure.h"
#include "MeasureList.h"

class ReadMidi;

class Score : public MeasureList {
    boost::rational<int> _time;
public:
    friend class ReadMidi;
    Score() {}
    void test() {}
};

#endif // SCORE_H
