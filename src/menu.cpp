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

uint8_t Menu::generatedLayoutsCount = 0;

void Menu::generateLayout(const char * menuName, const uint8_t& size, ...) {
  Menu::availableLayoutsNames[Menu::generatedLayoutsCount] = menuName;
  
  va_list vl;
  va_start(vl, size);

  for (uint8_t i = 0; i < size; i++) {
    Menu::availableLayouts[Menu::generatedLayoutsCount] = new Button(
  }
  ++Menu::generatedLayoutsCount;
}
