#include "menu.hpp"

Button::Button() : text("DEFAULT"), bType(ButtonType::clickable) {}
Button::Button(const char * txt, const ButtonType& bt) : text(txt), bType(bt) {}
void Button::setData(const char * txt, const ButtonType& bt) {
  text = txt;
  bType = bt;
}

Menu::Menu(Button * buttons, const uint8_t& n) : bArray(buttons), currentOptionIdx(0), size(n) {}
Menu::Menu(const uint8_t& n) : Menu(new Button[n], n) {}

void Menu::prev()  { currentOptionIdx = max(0, --currentOptionIdx);    }
void Menu::next()  { currentOptionIdx = min(size - 1, ++currentOptionIdx); }
void Menu::reset() { currentOptionIdx = 0; }
void Menu::setCurrentButtonData(const char * txt, const ButtonType& bt) { 
  bArray[currentOptionIdx].setData(txt, bt); 
}
const Button& Menu::getCurrentButtonData() { return bArray[currentOptionIdx]; }

