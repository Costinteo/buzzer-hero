#include "src/game.hpp"
#include <Tone.h>
#include "src/util.hpp"

#include "src/song.hpp"
Game * const buzzerHero = Game::getInstance();
//Tone t;
//Song jingle(Util::jingleBells, Util::JINGLE_BELLS_SIZE);
void setup() {
  buzzerHero->printMessage("Initiated game!");
  delay(1000);
  buzzerHero->clearRow(0);
  //t.begin(pincode::BUZZER);
}

void loop() {
  
  buzzerHero->update();
  /*
  if (!t.isPlaying()) {
    t.play(jingle.getCurrentPitch(), 350);
    jingle.next();
  }
  if (jingle.isFinished()) jingle.reset(); 
  */
}
