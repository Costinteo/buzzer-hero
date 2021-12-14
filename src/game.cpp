#include "game.hpp"

Game* Game::instance = nullptr;

/* constructor calls ledMatrix and lcd constructors as to not instantiate them more than once each */
Game::Game() : ledMatrix(pincode::DIN, pincode::CLK, pincode::LOAD, constants::DRIVER_NUM), \
               lcd(pincode::RS, pincode::ENABLE, pincode::D4, pincode::D5, pincode::D6, pincode::D7), \
               joy(pincode::VRX, pincode::VRY, pincode::SW),
               menu(nullptr, 0), \
               currentState(GameState::menuState), ledBrightness(constants::LED_MATRIX_BRIGHTNESS_DEFAULT), \
               lcdContrast(constants::LCD_CONTRAST_DEFAULT) { 
  
  ledMatrix.shutdown(constants::LED_MATRIX_CHIP, false);
  ledMatrix.setIntensity(constants::LED_MATRIX_CHIP, ledBrightness);
  ledMatrix.clearDisplay(constants::LED_MATRIX_CHIP);

  lcd.begin(constants::LCD_COLS, constants::LCD_ROWS);
  pinMode(pincode::CONTRAST, OUTPUT);

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

void Game::handleInput() {
  
  joy.update();

  switch (currentState) {
  case GameState::menuState:
    handleMenuInput();   
    break;
  case GameState::playState:
    //handlePlayInput();
    break;
  }
}

void Game::update() {
  handleInput();
  
  debugPrint(0, 1);
  
  draw();
  delay(50);
}

void Game::draw() {
  switch (currentState) {
  case GameState::menuState:
    drawMenu();
    break;
  case GameState::playState:
    drawPlay();
    break;
  default:
    lcd.clear();
    lcd.print("Unknown State");
    break;
  }
}

void Game::handleMenuInput() {
  /* used to iterate one option at a time */
  static bool menuMoved = false;
  switch (joy.getVerticalSense()) {
    /* lower for vertical means upwards */
    case JoystickSense::lower:
      if (!menuMoved) menu.prev();
      menuMoved = true;
      break;
    /* upper for vertical means downwards */
    case JoystickSense::upper:
      if (!menuMoved) menu.next();
      menuMoved = true;
      break;
    case JoystickSense::neutral:
      menuMoved = false;
      /* handle button type here */
      break;
    default:
      break;
  }

  const ButtonType& currButtonType = menu.getCurrentButtonType();
  if (joy.isButtonPressed()) {
    switch (currButtonType) {
      case ButtonType::enterMenu:
        break;
      case ButtonType::option:
        break;
      default:
        break;
    }
  }
}

/* MenuState methods */
void Game::drawMenu() {
  clearRow(0);
  lcd.print(menu.getCurrentButtonText());
}

/* PlayState methods */
void Game::drawPlay() {
  lcd.clear();
  lcd.print("Play State");
}

/* Led Matrix methods */
const LedControl& Game::getLedMatrix() const { return ledMatrix; }


/* LCD methods */
void Game::setCursor(const uint8_t& col = 0, const uint8_t& row = 0) { lcd.setCursor(col, row); }
void Game::clearRow(const uint8_t& row = 0, const uint8_t& numClear = constants::LCD_COLS) { 
  for (int i = 0; i < numClear; ++i) {
    lcd.setCursor(i, row);
    lcd.print(' ');
  }
  lcd.home();
}
void Game::printMessage(const char * msg) { lcd.print(msg); }
const LiquidCrystal& Game::getLcd()    const { return lcd; }
void Game::setContrast(const uint8_t& newContrast) { lcdContrast = newContrast; }


void Game::debugPrint(const uint8_t& col = 0, const uint8_t& row = 0) {
  char buffer[16];
  snprintf(buffer, sizeof(buffer), "x:%d y:%d mi:%d", 
          joy.getHorizontalSense(), joy.getVerticalSense(), menu.getCurrentIdx());
  lcd.setCursor(col, row);
  lcd.print(buffer);
  lcd.setCursor(0, 0);
}
