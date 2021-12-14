#include "menu.hpp"
#include "util.hpp"

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


Layout::Layout(Button * buttons, const uint8_t& n) : bArray(buttons), size(n) {}
const Button& Layout::operator[](const uint8_t& idx) const { return bArray[idx]; }
Layout& Layout::operator=(const Layout& lay) {
  bArray = lay.bArray;
  size = lay.size;
}
const uint8_t& Layout::getSize() { return size; }

Menu::Menu(Button * buttons, const uint8_t& n) : mLayout(buttons, n), currentOptionIdx(0) {}
Menu::Menu(const uint8_t& n) : Menu(new Button[n], n) {}

void Menu::prev()  { currentOptionIdx = max(0, currentOptionIdx - 1);    }
void Menu::next()  { currentOptionIdx = min(mLayout.getSize() - 1, currentOptionIdx + 1); }
void Menu::reset() { currentOptionIdx = 0; }

void Menu::setButtonLayout(const Button * lay, const uint8_t& n) {
  mLayout = Layout(lay, n);
}
/*
void Menu::setCurrentButtonData(const char * txt, const ButtonType& bt) { 
  bArray[currentOptionIdx].setData(txt, bt); 
}
*/
const Button&    Menu::getCurrentButton() { return mLayout[currentOptionIdx];       }
const char *     Menu::getCurrentButtonText() { return mLayout[currentOptionIdx].bText;  }
const ButtonType Menu::getCurrentButtonType() { return mLayout[currentOptionIdx].bType; }
const uint8_t& Menu::getCurrentIdx() { return currentOptionIdx; }


Layout Menu::availableLayouts[] = {
  Layout(constants::mainMenuLayout, constants::MAIN_MENU_SIZE),
  Layout(constants::optionsMenuLayout, constants::OPTIONS_MENU_SIZE)
};
