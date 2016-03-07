#include "MidiRead.h"

class note_tmp {
public:
    int start_tick;
    int fin_tick;
    int pitch;
    boost::rational<int> time;
    note_tmp() {
        start_tick = fin_tick = -1;
        time = 1;
    }
    int isFin() {return fin_tick >= 0;}
    int isStart() {return start_tick >= 0;}
};

class tempo_tmp {
public:
  int start_tick;
  int bpm;
};

MidiRead::MidiRead(Score** score, string dir, int trk, int min_note_size) {
    _score = score;
    _track = trk;
    _dir = dir;
    this->min_note_size = min_note_size;
}

MidiRead::~MidiRead() {

}

int MidiRead::round_off_tick(int tick) {
  //printf("%d -> %d\n", tick, int(float((((tick + (delta*2) / min_note_size)) / ((delta*4) / min_note_size)))) * ((delta*4) / min_note_size));
    return int(float((((tick + (delta*2) / min_note_size)) / ((delta*4) / min_note_size)))) * ((delta*4) / min_note_size);
}


/* ------------------------------------------------
 * note_tmpのlistをScoreに変換
 * ------------------------------------------------*/
void MidiRead::convert_notes(int min_pitch, int max_pitch) {
    *_score = new Score();
    Measure* measure;
    Note* note;
    int measure_num;
    int current_measure = -1; // こうしないとMeasureが作られない

    for(list<note_tmp>::iterator i = notes.begin(); i != notes.end(); i++) {
        measure_num = i->start_tick / (delta*4);
        for(; current_measure < measure_num; current_measure++) {
            measure = new Measure();
            measure->setTime(i->time);
            (*_score)->push_back(measure);
        }
        note = new Note();
        note->setPitch(i->pitch);
        note->setLength(round_off_tick(i->fin_tick - i->start_tick), delta*4);
        note->setPos(round_off_tick(i->start_tick) % (delta*4), delta*4);

        measure->push_back(note);
    }
    (*_score)->setMinPitch(min_pitch);
    (*_score)->setMaxPitch(max_pitch);
}

/* ------------------------------------------------
 * ノートが重なっているときは、後から鳴ったノートを無効化する
 * ------------------------------------------------*/
int MidiRead::readFile() {
    if(!midifile.read(_dir)) {
        puts("cant read midifile...");
        return 1;
    }
    delta = midifile.getTicksPerQuarterNote();
    midifile.joinTracks();
    MidiEvent* mev;
    int pitch; //  音階
    int min_pitch = 127;
    int max_pitch = 0;
    boost::rational<int> current_time = 1; //  今の拍子
    notes.clear();
    start_tick.clear();
    tmp_note = vector<note_tmp>(256);
    if(min_note_size <= 0) {min_note_size = delta;}

    for (int event=0; event < midifile[_track].size(); event++) {
        mev = &midifile[_track][event];
        if (event == 0) {
            deltatick = mev->tick;
        } else {
            deltatick = mev->tick - midifile[_track][event-1].tick;
        }
        // _trackのトラックだけを抽出
        if(mev->track == _track) {
            // MIDIイベントが
            // note onなら
            if(mev->isNoteOn()) {
                pitch = (int)(*mev)[1];
                if(!tmp_note[pitch].isStart()) {
                  tmp_note[pitch].start_tick = mev->tick;
                  tmp_note[pitch].pitch = pitch;
                  tmp_note[pitch].time = current_time;
                  //printf("SSS%d: %d\n", pitch, tmp_note[pitch].start_tick);
                }
                if(pitch < min_pitch) {
                    min_pitch = pitch;
                }
                if(pitch > max_pitch) {
                    max_pitch = pitch;
                }
            }
            // note offなら
            else if(mev->isNoteOff()) {
                pitch = (int)(*mev)[1];
                if(!tmp_note[pitch].isFin()) {
                  tmp_note[pitch].fin_tick = mev->tick;
                  printf("%d: %d<-%d\n", pitch, tmp_note[pitch].fin_tick, tmp_note[pitch].start_tick);
                  notes.push_back(tmp_note[pitch]);
                  tmp_note[pitch] = note_tmp();
                }
            }
            // 拍子変化なら
            else if((int)(*mev)[0] == 0xFF &&
                    (int)(*mev)[1] == 0x58 &&
                    (int)(*mev)[2] == 0x04) {
                current_time = boost::rational<int>((int)(*mev)[3], (int)(*mev)[4]);
            }
            // テンポ変化なら
            else if(mev->isTempo()) {
              tempo_tmp tempo;
              tempo.start_tick = mev->tick;
              tempo.bpm = mev->getTempoBPM();
              tmp_tempo.push_back(tempo);
            }
        }
    }
    convert_notes(min_pitch, max_pitch);
    return 0;
}
