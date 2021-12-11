#include "menu.hpp"

Button::Button() : bText("DEFAULT"), bType(ButtonType::option), bAction() {}
Button::Button(const char * txt, const ButtonType& bt, const Button * menuToEnter = nullptr) : \
              bText(txt), bType(bt), bAction(menuToEnter) {}
void Button::setData(const char * txt, const ButtonType& bt) {
  bText = txt;
  bType = bt;
}

Menu::Menu(const Button * buttons, const uint8_t& n) : bArray(buttons), currentOptionIdx(0), size(n) {}
Menu::Menu(const uint8_t& n) : Menu(new Button[n], n) {}

void Menu::prev()  { currentOptionIdx = max(0, currentOptionIdx - 1);    }
void Menu::next()  { currentOptionIdx = min(size - 1, currentOptionIdx + 1); }
void Menu::reset() { currentOptionIdx = 0; }

void Menu::setButtonLayout(const Button * layout, const uint8_t& n) {
  bArray = layout;
  size = n;
}
/*
void Menu::setCurrentButtonData(const char * txt, const ButtonType& bt) { 
  bArray[currentOptionIdx].setData(txt, bt); 
}
*/
const Button&    Menu::getCurrentButton() { return bArray[currentOptionIdx];       }
const char *     Menu::getCurrentButtonText() { return bArray[currentOptionIdx].bText;  }
const ButtonType Menu::getCurrentButtonType() { return bArray[currentOptionIdx].bType; }
const uint8_t& Menu::getCurrentIdx() { return currentOptionIdx; }
