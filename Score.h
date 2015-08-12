/*--------------------------------------------
 * 楽譜のデータ構造を表すクラス
 * MeasureListは小節のリスト
--------------------------------------------*/
#ifndef SCORE_H
#define SCORE_H

#include "Measure.h"
#include "MeasureList.h"
#include <QObject>

class ReadMidi;

class Score : public QObject, public MeasureList {
    Q_OBJECT
    boost::rational<int> _time;
public:
    friend class ReadMidi;
    explicit Score(QObject* parent = 0) : QObject(parent) {}
    Q_INVOKABLE void test() {}
};

#endif // SCORE_H
