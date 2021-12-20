#include "src/game.hpp"

Game * const buzzerHero = Game::getInstance();

void setup() {
  buzzerHero->printMessage("Initiated game!");
  delay(1000);
  buzzerHero->clearRow(0);
}

void loop() {
  
  buzzerHero->update();

}
