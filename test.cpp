#include "libscore.h"
#include <string>
#include <stdio.h>

int main(void) {
  Score* score;
  int track = 0;
  int min_note_size = -1; // 32分音符が最小
  string dir = "./test21.mid";
  MidiRead mr(&score, dir, track, min_note_size);
  mr.readFile();

  for(MIterator i = score->begin(); i != score->end(); i++) {
    for(NIterator j = i->begin(); j != i->end(); j++) {
      printf("%d:%d/%d\n", j->pitch(), j->length().numerator(), j->length().denominator());
    }
  }
  return 0;
}
