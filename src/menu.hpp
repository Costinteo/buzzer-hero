#include <stdint.h>
#include "Arduino.h"

#ifndef MENU_HPP
#define MENU_HPP

enum class ButtonType {
  clickable,  /* determines an action on click */
  sliding     /* value slider */
};

class Button {
  public:
    const char * text;
    ButtonType bType;

    Button();
    Button(const char *, const ButtonType&);

    void setData(const char *, const ButtonType&);
};

class Menu {
  private:
    Button* bArray;
    uint8_t currentOptionIdx;
    uint8_t size;
    
  public:

    Menu(Button*, const uint8_t&);
    Menu(const uint8_t&);
    
    void prev();
    void next();
    void reset();
    void setCurrentButtonData(const char *, const ButtonType&);
    const Button& getCurrentButtonData();
};

#endif
