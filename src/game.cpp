#include "game.hpp"
#include "menu.hpp"

Game* Game::instance = nullptr;

/* constructor calls ledMatrix and lcd constructors as to not instantiate them more than once each */
Game::Game() : ledMatrix(pincode::DIN, pincode::CLK, pincode::LOAD, Util::DRIVER_NUM), \
               lcd(pincode::RS, pincode::ENABLE, pincode::D4, pincode::D5, pincode::D6, pincode::D7), \
               joy(pincode::VRX, pincode::VRY, pincode::SW),
               menu(Util::mainMenuLayout), \
               buzz(), \
               currentSong(Util::jingleBells, Util::JINGLE_BELLS_SIZE), \
               currentState(GameState::menuState), ledBrightness(Util::LED_MATRIX_BRIGHTNESS_DEFAULT), \
               lcdContrast(Util::LCD_CONTRAST_DEFAULT), clearLcd(false), clearLed(false), buttonPressed(false) { 
  
  ledMatrix.shutdown(Util::LED_MATRIX_CHIP, false);
  ledMatrix.setIntensity(Util::LED_MATRIX_CHIP, ledBrightness);
  ledMatrix.clearDisplay(Util::LED_MATRIX_CHIP);

  lcd.begin(Util::LCD_COLS, Util::LCD_ROWS);
  pinMode(pincode::CONTRAST, OUTPUT);

  pinMode(pincode::BUTTON, INPUT_PULLUP);

  buzz.begin(pincode::BUZZER);

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

  /* button input could be refactored in a different function */
  buttonPressed = false;

  const uint8_t buttonDebounceDelay = 250;
  static bool btState = 1;
  static bool lastBtState = 1;
  static uint16_t lastPressed = 0;

  
  lastBtState = btState;
  btState = digitalRead(pincode::BUTTON);

  if (millis() - lastPressed > buttonDebounceDelay && !btState && lastBtState) {
    lastPressed = millis();
    buttonPressed = true;
  }

  switch (currentState) {
  case GameState::menuState:
    handleMenuInput();   
    break;
  case GameState::playState:
    handlePlayInput();
    break;
  }
}

void Game::update() {
  handleInput();
  //debugPrint(0, 1);
  
  
  // play song
  if (currentSong.isFinished()) currentSong.reset();
  if (!buzz.isPlaying()) {
    currentSong.next();
    buzz.play(currentSong.getCurrentPitch(), 250);
  }

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

/* MenuState methods */
void Game::drawMenu() {
  lcd.home();
  if (clearLcd) {
    lcd.clear();
    clearLcd = false;
  }

  lcd.print(menu.getCurrentButtonText());
  lcd.setCursor(0,1);
  switch (menu.getCurrentButtonType()) {
    case ButtonType::enterMenu:
      lcd.print("ENTER MENU");
      break;
    case ButtonType::option:
      lcd.print("OPTION");
      break;
    case ButtonType::play:
      lcd.print("PLAY");
      break;
    case ButtonType::info:
      lcd.print(menu.getCurrentButtonAction().infoToPrint);
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
  
  if (menuMoved) clearLcd = true;

  const ButtonType& currButtonType = menu.getCurrentButtonType();
  if (joy.isButtonPressed()) {
    clearLcd = true;
    switch (currButtonType) {
      case ButtonType::play:
        currentState = GameState::playState;
        switchMenu(&Util::playMenuLayout);
        break;
      case ButtonType::enterMenu:
        switchMenu(menu.getCurrentButtonAction().menuToEnter);
        break;
      case ButtonType::option:
        break;
      default:
        break;
    }
  }
}

void Game::switchMenu(const Layout * newMenuLayout) {
  menu.setButtonLayout(newMenuLayout);
  menu.reset();
}

/* PlayState methods */
void Game::drawPlay() {
  lcd.home();
  lcd.clear();
  lcd.print(menu.getCurrentButtonText());
}

void Game::handlePlayInput() {
  if (buttonPressed) {
    menu.setCurrentButtonText("GREAT");
  } else {
    menu.setCurrentButtonText("AAAAAAAAAA");
  }
}


/* Led Matrix methods */
const LedControl& Game::getLedMatrix() const { return ledMatrix; }


/* LCD methods */
void Game::setCursor(const uint8_t& col = 0, const uint8_t& row = 0) { lcd.setCursor(col, row); }
void Game::clearRow(const uint8_t& row = 0, const uint8_t& numClear) { 
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
