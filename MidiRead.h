/*--------------------------------------------
 * MIDI読み込みクラス
--------------------------------------------*/
#ifndef MIDIREAD_H
#define MIDIREAD_H
#include "Score.h"
#include <midifile/MidiFile.h>
#include <midifile/Options.h>
#include <string>
#include <list>
#include <QObject>

class note_tmp;

class MidiRead {
    Score** _score;
    string _dir;
    MidiFile midifile;
    int _track;
    int delta; // ４分音符あたりのtick数
    list<int> start_tick;
    vector<note_tmp> tmp_note;
    list<note_tmp> notes;
    int deltatick; // 次のイベントまでの待ち時間だったと思う
                   // 今見てるイベントを実行するまでの待ち時間かも？←たぶんこっち
    int min_note_size;

public:
    MidiRead(Score** score, string dir, int trk = 0, int min_note_size = 32);
    ~MidiRead();
    void convert_notes();
    int round_off_tick(int tick);
    int readFile();
};

#endif // MIDIREAD_H
