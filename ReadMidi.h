/*--------------------------------------------
 * MIDIファイルから楽譜を読み込むクラス
--------------------------------------------*/
#ifndef READMIDI_H
#define READMIDI_H
#include <boost/rational.hpp>
#include <list>
#include <vector>
#include "Score.h"

class ReadMidi {
    Score* score;
    std::string file_name;
    std::string copy_right;
    long long dtime;
    int readed_length;
    long long current_dtime; // 現在のデルタタイムの合計
    long long current_delta; // 現在のデルタタイム
    long long old_delta;
    boost::rational<int> time;
    std::vector<Noteset> noteset;
    std::list<Note> tmp_notes;
    std::list<long long> tmp_dtime;
    Score* score;
    unsigned char last_event;
    int track_num;
public:
    ReadMidi(Score*, std::string);
    ~ReadMidi();

    void clear_readed_length();
    bool checkFormat();
    bool checkHeader(FILE *fp);
    void meta_data(FILE *fp);
    void midi_event(FILE *fp, unsigned char event);
    bool readBody(FILE *fp);
    int read_delta(FILE *fp);
    int read_var_length(FILE *fp);
    void readFileDataL(unsigned char *data, FILE *fp, int data_length);
    void convertNotes();
    int calcMeasureNum(int time);

    void readData();
};

#endif // READMIDI_H
