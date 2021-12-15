#include "menu.hpp"

Button::Button(const char * txt = "DEFAULT", const ButtonType& bt = ButtonType::option) : bText(txt), bType(bt), bAction() {}
Button::Button(const char * txt, const ButtonType& bt, const Button * menuToEnter) : \
              bText(txt), bType(bt), bAction(menuToEnter) {}
Button::Button(const char * txt, const ButtonType& bt, uint8_t * valueToChange) : \
              bText(txt), bType(bt), bAction(valueToChange) {}
Button::Button(const char * txt, const ButtonType& bt, const char * infoToPrint) : \
              bText(txt), bType(bt), bAction(infoToPrint) {}

void Button::setData(const char * txt, const ButtonType& bt) {
  bText = txt;
  bType = bt;
}


Layout::Layout(const uint8_t& n) : bArray(new Button[n]), size(n), tailIdx(0) {}
void Layout::addButton(Button * bt) {
  if (tailIdx >= size) return;
  
  /* copy buttons */
  bArray[tailIdx++] = *bt;

}

void Menu::generateLayout(const uint8_t& n, ...) {
  va_list vl;
  va_start(vl, n);
  if (n != size) {
    if (layout) delete[] layout;
    layout = new Button[n];
    size = n;
  } 
    
  for (uint8_t i = 0; i < n; i++) {
    addButton(va_arg(vl, Button*));
  }

  va_end(vl);
}

Menu::Menu() : layout(nullptr), currentOptionIdx(0), size(0) {}
Menu::Menu(Button * buttons, const uint8_t& n) : layout(buttons), currentOptionIdx(0), size(n) {}
Menu::Menu(const uint8_t& n) : Menu(new Button[n], n) {}

void Menu::prev()  { currentOptionIdx = max(0, currentOptionIdx - 1);    }
void Menu::next()  { currentOptionIdx = min(size - 1, currentOptionIdx + 1); }
void Menu::reset() { currentOptionIdx = 0; }

void Menu::setButtonLayout(const Button * lay, const uint8_t& n) {
  layout = lay;
  size = n;
}
/*
void Menu::setCurrentButtonData(const char * txt, const ButtonType& bt) { 
  bArray[currentOptionIdx].setData(txt, bt); 
}
*/
const Button&    Menu::getCurrentButton() { return layout[currentOptionIdx];       }
const char *     Menu::getCurrentButtonText() { return layout[currentOptionIdx].bText;  }
const ButtonType Menu::getCurrentButtonType() { return layout[currentOptionIdx].bType; }
const uint8_t& Menu::getCurrentIdx() { return currentOptionIdx; }

