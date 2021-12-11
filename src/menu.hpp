#include <stdint.h>
#include "Arduino.h"

#ifndef MENU_HPP
#define MENU_HPP

enum class ButtonType {
  enterMenu,      /* enter a new menu on click */
  option,         /* value slider */
  info            /* simple info  */
};

class Button {
  public:
    const char * bText;
    ButtonType bType;
    union act {
      act() { memset(this, 0, sizeof(*this)); }
      act(const Button * m) { menuToEnter = m; }

      const Button * menuToEnter;
      uint8_t *      valueToChange;
    } bAction;

    Button();
    Button(const char *, const ButtonType&, const Button * = nullptr);

    void setData(const char *, const ButtonType&);
};

class Menu {
  private:
    const Button* bArray;
    uint8_t currentOptionIdx;
    uint8_t size;
    
  public:

    Menu(const Button*, const uint8_t&);
    Menu(const uint8_t&);
    
    void prev();
    void next();
    void reset();
    void setButtonLayout(const Button*, const uint8_t&);
    void setCurrentButtonData(const char *, const ButtonType&);
    const Button&    getCurrentButton();
    const char *     getCurrentButtonText();
    const ButtonType getCurrentButtonType();
    const uint8_t& getCurrentIdx();
};

#endif
