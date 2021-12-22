#ifndef MENU_HPP
#define MENU_HPP
#include <stdint.h>
#include <stdarg.h>
#include <Arduino.h>

enum class ButtonType {
  play,           /* change state to  play */
  enterMenu,      /* enter a new menu on click */
  option,         /* value slider */
  info            /* simple info  */
};

struct Layout;

class Button {
  public:
    const char * bText;
    ButtonType bType;
    union act {
      act() { memset(this, 0, sizeof(*this)); }
      act(const Layout * m) { menuToEnter = m; }
      act(uint8_t * v) { valueToChange = v; }
      act(const char * i) { infoToPrint = i; }

      const Layout * menuToEnter;
      uint8_t *      valueToChange;
      const char *   infoToPrint;
    } bAction;

    Button(const char * = "DEFAULT", const ButtonType& = ButtonType::option);
    Button(const char *, const ButtonType&, const Layout *);
    Button(const char *, const ButtonType&, uint8_t *);
    Button(const char *, const ButtonType&, const char *);

    void setData(const char *, const ButtonType&);
};

struct Layout {
  uint8_t size;
  Button * bArray;
};


class Menu {
  private:
    const Layout* layout;
    uint8_t currentOptionIdx;
  
  public:
    Menu();
    Menu(const Layout&);
    
    void prev();
    void next();
    void reset();
    void setButtonLayout(const Layout *);
    void setCurrentButtonText(const char *);
    const Button&     getCurrentButton();
    const char *      getCurrentButtonText();
    const ButtonType  getCurrentButtonType();
    const Button::act getCurrentButtonAction();
    const uint8_t& getCurrentIdx();

    void generateLayout(const uint8_t&, ...);
};


#endif
