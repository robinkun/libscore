#include "libscore.h"
#include <string>
#include <stdio.h>

int main(void) {
  Score* score;
  int track = 0;
  int min_note_size = 32; // 32分音符が最小
  string dir = "./test.mid";
  MidiRead mr(&score, dir, track, min_note_size);
  mr.readFile();

  for(MIterator i = score->first(); i != score->end(); i++) {
    for(NIterator j = i->first(); j != i->end(); j++) {
      printf("%d\n", j->pitch());
    }
  }
  return 0;
}
