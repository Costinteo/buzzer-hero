#include "game.hpp"

Game* Game::instance = nullptr;

/* constructor calls ledMatrix and lcd constructors as to not instantiate them more than once each */
Game::Game() : ledMatrix(pincode::DIN, pincode::CLK, pincode::LOAD, constants::DRIVER_NUM), \
               lcd(pincode::RS, pincode::ENABLE, pincode::D4, pincode::D5, pincode::D6, pincode::D7), \
               joy(pincode::VRX, pincode::VRY, pincode::SW),
               menu(constants::MAIN_MENU_SIZE), \
               currentState(GameState::menuState) { 
  
  ledMatrix.shutdown(constants::LED_MATRIX_CHIP, false);
  ledMatrix.setIntensity(constants::LED_MATRIX_CHIP, constants::LED_MATRIX_BRIGHTNESS);
  ledMatrix.clearDisplay(constants::LED_MATRIX_CHIP);

  lcd.begin(constants::LCD_COLS, constants::LCD_ROWS);
  pinMode(pincode::CONTRAST, OUTPUT);

  menu.setCurrentButtonData("Play", ButtonType::clickable);
  menu.next();
  menu.setCurrentButtonData("Options", ButtonType::clickable);
  menu.next();
  menu.setCurrentButtonData("About", ButtonType::clickable);
  menu.reset();
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
  
  /*
  char buffer[16];
  snprintf(buffer, sizeof(buffer), "x:%d y:%d, b:%d", 
          joy.getHorizontalSense(), joy.getVerticalSense(), joy.isButtonPressed());
  lcd.clear();
  lcd.print(buffer);
  delay(50);
  */
  draw();
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
  switch (joy.getVerticalSense()) {
    /* lower for vertical means upwards */
    case JoystickSense::lower:
      menu.prev();
      break;
    /* upper for vertical means downwards */
    case JoystickSense::upper:
      menu.next();
      break;
    case JoystickSense::neutral:
      /* handle button type here */
      break;
    default:
      break;
  }
}

/* MenuState methods */
void Game::drawMenu() {
  lcd.clear();
  lcd.print(menu.getCurrentButtonData().text);
}

/* PlayState methods */
void Game::drawPlay() {
  lcd.clear();
  lcd.print("Play State");
}

/* Led Matrix methods */
const LedControl& Game::getLedMatrix() const { return ledMatrix; }


/* LCD methods */
void Game::printMessage(const char * msg) { lcd.print(msg); }
const LiquidCrystal& Game::getLcd()    const { return lcd; }
void Game::setContrast(const uint8_t& newContrast) { lcdContrast = newContrast; }

