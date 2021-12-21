#include "menu.hpp"

Button::Button(const char * txt = "DEFAULT", const ButtonType& bt = ButtonType::option) : bText(txt), bType(bt), bAction() {}
Button::Button(const char * txt, const ButtonType& bt, const Layout * menuToEnter) : \
              bText(txt), bType(bt), bAction(menuToEnter) {}
Button::Button(const char * txt, const ButtonType& bt, uint8_t * valueToChange) : \
              bText(txt), bType(bt), bAction(valueToChange) {}
Button::Button(const char * txt, const ButtonType& bt, const char * infoToPrint) : \
              bText(txt), bType(bt), bAction(infoToPrint) {}

void Button::setData(const char * txt, const ButtonType& bt) {
  bText = txt;
  bType = bt;
}

Menu::Menu() : layout(nullptr) {}
Menu::Menu(const Layout& lay) : layout(&lay), currentOptionIdx(0) {}

void Menu::prev()  { currentOptionIdx = max(0, currentOptionIdx - 1);    }
void Menu::next()  { currentOptionIdx = min(layout->size - 1, currentOptionIdx + 1); }
void Menu::reset() { currentOptionIdx = 0; }

void Menu::setButtonLayout(const Layout * newLayout) {
  layout = newLayout;
}

const Button&     Menu::getCurrentButton()       { return layout->bArray[currentOptionIdx];         }
const char *      Menu::getCurrentButtonText()   { return layout->bArray[currentOptionIdx].bText;   }
const ButtonType  Menu::getCurrentButtonType()   { return layout->bArray[currentOptionIdx].bType;   }
const Button::act Menu::getCurrentButtonAction() { return layout->bArray[currentOptionIdx].bAction; }
const uint8_t& Menu::getCurrentIdx() { return currentOptionIdx; }

