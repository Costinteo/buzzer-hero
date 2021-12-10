#include "src/util.hpp"
#include "src/game.hpp"
#include "src/joystick.hpp"


Game * const buzzerHero = Game::getInstance();

void setup() {
  buzzerHero->printMessage("Initiated game!");
  delay(1000);
}

void loop() {
  
  buzzerHero->update();

}
