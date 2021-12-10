#include <LiquidCrystal.h>
#include <LedControl.h>
#include <stdio.h>
#include "Arduino.h"
#include "util.hpp"
#include "joystick.hpp"


#ifndef GAME_HPP
#define GAME_HPP

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

    Joystick       joy;

    /* METHODS */
    Game();


  public:
    static Game * const getInstance();
    
    void update();
    void draw();
    
    /* Menu methods */
    void updateMenu();
    void drawMenu();

    /* Play methods */
    void updatePlay();
    void drawPlay();

    /* Led Matrix methods */
    const LedControl&      getLedMatrix() const;

    /* LCD methods */
    void printMessage(const char *);
    const LiquidCrystal&   getLcd() const;
    void setContrast(const uint8_t& newContrast);

    
    ~Game();
};



#endif
