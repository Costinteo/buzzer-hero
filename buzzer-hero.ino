#include "src/util.hpp"
#include "src/game.hpp"
#include "src/joystick.hpp"
#include "src/menu.hpp"

/* MENU LAYOUTS */
Button mainMenu[] = {
  Button("Play",       ButtonType::enterMenu, constants::playMenuLayout),
  Button("Options",    ButtonType::enterMenu, constants::optionsMenuLayout),
  Button("About",      ButtonType::enterMenu, constants::aboutMenuLayout)
};

Button optionsMenu[] = {
  Button("Back",       ButtonType::enterMenu, constants::mainMenuLayout),
  Button("Contrast",   ButtonType::option),
  Button("Brightness", ButtonType::option),
  Button("Difficulty", ButtonType::option)
};

Game * const buzzerHero = Game::getInstance();

void setup() {
  util::linkMenuPointers(constants::LAYOUTS_NUM, nullptr, mainMenu, optionsMenu);
  buzzerHero->printMessage("Initiated game!");
  delay(1000);
  buzzerHero->clearRow(0);
}

void loop() {
  
  buzzerHero->update();

}
