#include "ReadMidi.h"
#include "MIterator.h"
#include "NIterator.h"
#include <fstream>
#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// file_nameは読み込むデータ
ReadMidi::ReadMidi(Score* score, std::string file_name) {
  this->file_name = file_name;
  dtime = 0x01E0;
  readed_length = 0;
  current_dtime = 0;
  current_delta = 0;
  last_event = 0xFF;
  track_num = 0;
  time = boost::rational<int>(1);
  noteset = std::vector<Noteset>(256);
  readData();
  current_note = measures[0]->notes.begin();
  current_measure = 0;
}

int ReadMidi::calcMeasureNum(int time) {
  if(time%(dtime*4) > 0) {
    time += dtime*4;
  }
  return time / (dtime*4);
}

bool ReadMidi::checkFormat() {
  return true;
}

bool ReadMidi::checkHeader(FILE *fp) {
  unsigned char data[5];
  int data_length;

  readFileDataL(data, fp, 4);
  data[4] = '\0';
  // ファイルの先頭がMThdじゃないとヤだ
  try {
      if(!(data[0] == 0x4D && data[1] == 0x54 && data[2] == 0x68 && data[3] == 0x64)) {
        throw("MThd Error.");
      }
      // データ長が00000006じゃないとヤだ
      readFileDataL(data, fp, 4);
      if(!(data[0] == data[1] == data[2] == 0 && data[3] == 0x06)) {
        throw("Data length of Header chunk Error.");
      }
      // フォーマットが1じゃないとヤだ
      readFileDataL(data, fp, 2);
      if(!(data[0] == 0 && data[1] == 0x01)) {
        throw("SMF Format Error.");
      }
  } catch(std::string message) {
      std::cout << message;
  }

  // トラック数は読み飛ばす。うるさい黙れ
  readFileDataL(data, fp, 2);
  track_num = data[0];
  track_num = track_num << 8;
  track_num = data[1];
  // デルタタイムの単位の指定
  readFileDataL(data, fp, 2);

  dtime = (int)data[0] * 0x0100 + (int)data[1];

  return true;
}

void ReadMidi::clear_readed_length() {
  readed_length = 0;
}

void ReadMidi::meta_data(FILE *fp) {
  unsigned char data[5], event;
  unsigned int length;
  readFileDataL(&event, fp, 1);

  length = read_var_length(fp);
  // 拍子の設定
  if(event == 0x58) {
    readFileDataL(data, fp, 4);
    time = boost::rational<int>(data[0], pow(2, data[1]));
  } else {
    for(int i = 0; i < length; i++)
      readFileDataL(data, fp, 1);
  }
}

void ReadMidi::convertNotes() {
  int measure_num = calcMeasureNum(current_dtime);
  //measures = std::vector<Measure*>(calcMeasureNum(current_dtime));
  //printf("&&&&&&%d\n", calcMeasureNum(current_dtime));
  for(int i = 0; i < score->size(); i++) {
    measures[i] = new Measure(i, 0, 13);
    SheetPos p;
    p.measure = measures[i];
    Time t(time, p);
    measures[i]->set_time(t);
  }

  std::list<long long>::iterator i;
  std::list<Note>::iterator j;
  MIterator mi;
  mi = score->first();
  SheetPos p;
  Note tmp_;
  i = tmp_dtime.begin();
  j = tmp_notes.begin();
  //std::cout << std::dec;

  for(int k = 0; k < measure_num; k++) {
    int m_num = *i / (dtime*4);
    p.measure = measures[m_num];
    p.pos = (*j).pos.pos;

    /*
    std::cout << "pos = " << p.pos << std::endl;
    std::cout << "pitch = " << ((*j).get_pitch()) << std::endl;
    std::cout << "length = " << ((*j).get_length()) << std::endl;
    */
    tmp_ = Note((*j).get_pitch(), (*j).get_length(), p);
    tmp_ = new Note();
    tmp_->setPitch(j->pitch());
    tmp_->setLength(j->length());
    tmp_->setPos();
    measures[m_num]->add_note(tmp_);
    mi->push_back(new Note());
    i++;
    j++;
  }
}

void ReadMidi::midi_event(FILE *fp, unsigned char event) {
  unsigned char data[5], channel;
  last_event = event;

  channel = event%0x10;

  if((event>>4 == 0xA) || (event>>4 == 0xE)) {
    // 読み飛ばす
    readFileDataL(data, fp, 2);
    return;
  } else if((event>>4 == 0xC) || (event>>4 == 0xD)) {
    readFileDataL(data, fp, 1);
    return;
  } else if(event>>4 == 0xB) {
    // 0x7Eだとビット数が4になる時があるので、
    // 3つ飛ばさないと上手く読み込めない時があるかも
    readFileDataL(data, fp, 2);
    return;
  } else if(event>>4 == 9) {
    // ノートオン
    if(channel == 0) {
      readFileDataL(data, fp, 2);

      // ベロシティが0ならノートオフ
      if(data[1] == 0) {
        noteset[data[0]].set_end(current_dtime);
        Note tmp = Note(data[0] - REF_POINT, noteset[data[0]].flength(dtime), SheetPos(nullptr, noteset[data[0]].fpos(dtime)));
        tmp_notes.push_back(tmp);
        tmp_dtime.push_back(current_dtime);
        //printf("%d, %d\n", noteset[data[0]].start ,noteset[data[0]].end);
        //printf("==%d\n", current_dtime);
      }
      else {
        noteset[data[0]].set_start(current_dtime);
      }
    } else {
      // 読み飛ばす
      readFileDataL(data, fp, 2);
      return;
    }
  } else if(event>>4 == 8) {
    // ノートオフ
    if(channel == 0) {
      readFileDataL(data, fp, 2);
      noteset[data[0]].set_end(current_dtime + current_delta);
      Note tmp = Note(data[0] - REF_POINT, noteset[data[0]].flength(dtime), SheetPos(nullptr, noteset[data[0]].fpos(dtime)));
      tmp_notes.push_back(tmp);
      tmp_dtime.push_back(current_dtime);
    } else {
      // 読み飛ばす
      readFileDataL(data, fp, 2);
      return;
    }
  }
}

bool ReadMidi::readBody(FILE *fp) {
  unsigned char data[5];
  int data_length;
  int delta;



  //for(int i = 0; i < track_num; i++) {
    // トラックのヘッダチャンク読み込み
    readFileDataL(data, fp, 4);
    data[4] = '\0';
    if(ustrcmp(data, (unsigned char *)"MTrk")) {
      puts("MTrk Error.");
      myerror(FILE_MTrk_ERROR);
    }
    //std::cout << std::endl;
    readFileDataL(data, fp, 4);

    data_length = 0;
    for(int i = 0; i < 4; i++) {
      data_length = data_length << 8;
      data_length += data[i];
    }
    //std::cout << "data_length = " << std::hex<<data_length << std::endl;

    // 実データ読み込み
    current_dtime = 0;
    current_delta = 0;

    clear_readed_length();
    for(; readed_length < data_length;) {
      delta = read_delta(fp);
      readFileDataL(data, fp, 1);
      int now_event = data[0];
      if(data[0] >> 7) {
        if(data[0]>>4 == 0xF) {
          if(data[0]%0x10 == 0x0 || data[0]%0x10 == 0x7) {
            int length = read_var_length(fp);
            unsigned char tmp;
            for(int i = 0; i < length; i++)
              readFileDataL(&tmp, fp, 1);
          } else if(data[0]%0x10 == 0xF) {
            // メタデータ
            meta_data(fp);
          }
        } else if(data[0]>>4 >= 0x8 && data[0]>>4 <= 0xE) {
          midi_event(fp, data[0]);
        }
        last_event = now_event;
      } else if(last_event>>4 >= 0x8 && last_event>>4 <= 0xE) {
        // ステータスバイトが省略されている時，ファイルポインタは予定より1つ進んでいることになるから、ひとつ戻す
        fseek(fp, -1, SEEK_CUR);
        readed_length--;
        midi_event(fp, last_event);
      }
      //puts("");
    }
  //}
  current_dtime += current_delta;

  return true;
}

// file_nameからデータを読み込む
bool ReadMidi::readData() {
  FILE *fp;

  if((fp = fopen(file_name.c_str(), "r")) == NULL) {
    puts("File open error.");
    myerror(FILE_READ_ERROR);
  }
  checkHeader(fp);
  readBody(fp);
  convertNotes();

  return 0;
}

int ReadMidi::read_delta(FILE *fp) {
  int delta = read_var_length(fp);
  current_dtime += delta;
  current_delta = delta;
  /*
  printf("current_dtime = %d\n", current_dtime);
  printf("current_delta = %d\n", current_delta);
  */

  return delta;
}

int ReadMidi::read_var_length(FILE *fp) {
  unsigned char data[2];
  int cnt = 0;
  int delta = 0;

  // 実データのデータ長読み込み
  do {
    readFileDataL(data, fp, 1);
    delta = delta << 7;
    delta += data[0] % 0x80;
    cnt++;
  } while(data[0] >> 7 && cnt < 4);
  //std::cout << "delta = " << std::hex << delta << std::endl;

  return delta;
}

void ReadMidi::readFileDataL(unsigned char *data, FILE *fp, int data_length) {
  readed_length += data_length;
  readFileData(data, fp, data_length);

  /*
  for(int i = 0; i < data_length; i++) {
    printf(" %X", data[i]);
  }*/
}

