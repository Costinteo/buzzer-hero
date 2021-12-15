#ifndef MENU_HPP
#define MENU_HPP
#include <stdint.h>
#include <stdarg.h>
#include "Arduino.h"


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
      act(uint8_t * v) { valueToChange = v; }
      act(const char * i) { infoToPrint = i; }

      const Button * menuToEnter;
      uint8_t *      valueToChange;
      const char *   infoToPrint;
    } bAction;

    Button(const char * = "DEFAULT", const ButtonType& = ButtonType::option);
    Button(const char *, const ButtonType&, const Button *);
    Button(const char *, const ButtonType&, uint8_t *);
    Button(const char *, const ButtonType&, const char *);

    void setData(const char *, const ButtonType&);
};

class Layout {
  private:
    Button* bArray;
    uint8_t size;
    uint8_t tailIdx;

    Layout(const uint8_t& = 0);
    void addButton(Button*);

  public:
    static Layout * generateLayout(const uint8_t&, ...);
};

class Menu {
  private:
    const Button* layout;
    uint8_t currentOptionIdx;
    uint8_t size;
  
    void addButton(Button*);
  public:
  
    Menu();
    Menu(Button *, const uint8_t&);
    Menu(const uint8_t&);
    
    void prev();
    void next();
    void reset();
    void setButtonLayout(const Button *, const uint8_t&);
    void setCurrentButtonData(const char *, const ButtonType&);
    const Button&    getCurrentButton();
    const char *     getCurrentButtonText();
    const ButtonType getCurrentButtonType();
    const uint8_t& getCurrentIdx();

    void generateLayout(const uint8_t&, ...);
};

#endif
