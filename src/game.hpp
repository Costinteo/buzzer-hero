#include <LiquidCrystal.h>
#include <LedControl.h>
#include "util.hpp"

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
    /* members */
    static Game *  instance;
    GameState      currentState;

    LiquidCrystal  lcd;
    uint8_t        lcdContrast;

    LedControl     ledMatrix;

    /* methods */
    Game();


  public:
    static Game * const getInstance();
    
    void update();
    void draw();
    
    /* LCD methods */
    void updateLcd();
    void drawLcd();


    /* LED Matrix methods */
    void updateLedMatrix();
    void drawLedMatrix();


    /* getters */
    const LedControl&      getLedMatrix() const;
    const LiquidCrystal&   getLcd() const;
  
    /* setters */
    void setContrast(const uint8_t& newContrast);

    
    ~Game();
};



#endif
