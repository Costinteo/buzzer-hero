#ifndef GAME_HPP
#define GAME_HPP

#include <LiquidCrystal.h>
#include <LedControl.h>
#include <stdio.h>
#include <string.h>
#include "Arduino.h"
#include "util.hpp"
#include "joystick.hpp"
#include "menu.hpp"

/* game states */
enum class GameState {
  menuState,
  playState
};

/* game class singleton */
class Game {
  private:
    /* MEMBERS */
    static Game *  instance;
    GameState      currentState;

    LiquidCrystal  lcd;
    uint8_t        lcdContrast;

    LedControl     ledMatrix;
    uint8_t        ledBrightness;

    Joystick       joy;

    Menu           menu;
    /* METHODS */
    Game();
    
    /* Menu methods */
    void handleMenuInput();
    void updateMenu();
    void drawMenu();

    /* Play methods */
    void handlePlayInput();
    void updatePlay();
    void drawPlay();


  public:
    static Game * const getInstance();
    
    void handleInput();
    void update();
    void draw();
    
    /* Led Matrix methods */
    const LedControl&      getLedMatrix() const;

    /* LCD methods */
    void setCursor(const uint8_t& = 0, const uint8_t& = 0);
    void clearRow(const uint8_t&, const uint8_t& = constants::LCD_COLS);
    void printMessage(const char *);
    const LiquidCrystal&   getLcd() const;
    void setContrast(const uint8_t& newContrast);

    void debugPrint(const uint8_t&, const uint8_t&);    
    ~Game();
};



#endif
