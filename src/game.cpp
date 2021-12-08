#include "game.hpp"

Game* Game::instance = nullptr;

/* constructor calls ledMatrix and lcd constructors as to not instantiate them more than once each */
Game::Game() : ledMatrix(pincode::DIN, pincode::CLK, pincode::LOAD, constants::DRIVER_NUM), \
               lcd(pincode::RS, pincode::ENABLE, pincode::D4, pincode::D5, pincode::D6, pincode::D7) {
  
  ledMatrix.shutdown(constants::LED_MATRIX_CHIP, false);
  ledMatrix.setIntensity(constants::LED_MATRIX_CHIP, constants::LED_MATRIX_BRIGHTNESS);
  ledMatrix.clearDisplay(constants::LED_MATRIX_CHIP);

  lcd.begin(constants::LCD_COLS, constants::LCD_ROWS);

  currentState = GameState::menuState;

}

Game::~Game() {
  Game::instance = nullptr;
}

Game * const Game::getInstance() {
  if (Game::instance == nullptr) {
    Game::instance = new Game();
  }
  return Game::instance;
}

void Game::update() {
  switch (currentState) {
  case GameState::menuState:
    break;
  case GameState::playState:
    break;
  }

  draw();
}

void Game::draw() {
  switch (currentState) {
  case GameState::menuState:
    lcd.clear();
    lcd.print("Menu State");
    break;
  case GameState::playState:
    lcd.clear();
    lcd.print("Play State");
    break;
  default:
    lcd.clear();
    lcd.print("Unknown State");
    break;
  }
}

/* LCD methods */
void Game::drawLcd() {
  lcd.clear();
  lcd.print("Current state:");
  
}

/* LED Matrix methods */



/* getters */
const LedControl& Game::getLedMatrix() const { return ledMatrix; }
const LiquidCrystal& Game::getLcd()    const { return lcd; }

/* setters */
void Game::setContrast(const uint8_t& newContrast) { lcdContrast = newContrast; }
