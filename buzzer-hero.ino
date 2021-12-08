#include <LiquidCrystal.h>
#include <LedControl.h>
#include "src/util.hpp"
#include "src/game.hpp"


Game * const buzzerHero = Game::getInstance();

void setup() {
  
  pinMode(pincode::CONTRAST, OUTPUT);  


}

void loop() {
  
  buzzerHero->draw();
  for (uint8_t i = 0; i < 256; ++i) {
        analogWrite(pincode::CONTRAST, i);
        delay(5);
  }
  delay(500);
  for (uint8_t i = 255; i >= 0; --i) {
        analogWrite(pincode::CONTRAST, i);
        delay(5);
  }
  delay(500);


}
