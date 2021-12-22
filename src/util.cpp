#include "util.hpp"

Button Util::mainMenuButtonArray[] = {
  Button("Play",    ButtonType::play),
  Button("Options", ButtonType::enterMenu, &optionsMenuLayout),
  Button("About",   ButtonType::enterMenu, &aboutMenuLayout)
};

Button Util::playMenuButtonArray[] = {
  Button("Buzz that buzzer!", ButtonType::info, "")
};

Button Util::optionsMenuButtonArray[] = {
  Button("Back",       ButtonType::enterMenu, &mainMenuLayout),
  Button("Contrast",   ButtonType::option),
  Button("Brightness", ButtonType::option),
  Button("Difficulty", ButtonType::option)
};

Button Util::aboutMenuButtonArray[] = {
  Button("Back",        ButtonType::enterMenu, &mainMenuLayout),
  Button("Buzzer Hero", ButtonType::info, "Led matrix game"),
  Button("Author",      ButtonType::info, "Costin Grigore"),
  Button("Github",      ButtonType::info, "Costinteo")

};

const Layout Util::mainMenuLayout = {
  MAIN_MENU_SIZE,
  mainMenuButtonArray
};

const Layout Util::playMenuLayout = {
  PLAY_MENU_SIZE,
  playMenuButtonArray
};

const Layout Util::optionsMenuLayout = {
  OPTIONS_MENU_SIZE,
  optionsMenuButtonArray
};

const Layout Util::aboutMenuLayout = {
  ABOUT_MENU_SIZE,
  aboutMenuButtonArray
};

const uint16_t Util::jingleBells[] = { 
  NOTE_E4, NOTE_E4, NOTE_E4,       0, NOTE_E4, NOTE_E4, NOTE_E4,       0,
  NOTE_E4, NOTE_G4, NOTE_C4, NOTE_D4, NOTE_E4,       0,       0,       0,
  NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4,
  NOTE_E4, NOTE_D4, NOTE_D4, NOTE_E4, NOTE_D4, NOTE_G4,       0,       0,
  NOTE_E4, NOTE_E4, NOTE_E4,       0, NOTE_E4, NOTE_E4, NOTE_E4,       0,
  NOTE_E4, NOTE_G4, NOTE_C4, NOTE_D4, NOTE_E4,       0,       0,       0,
  NOTE_E4, NOTE_D4, NOTE_D4, NOTE_E4, NOTE_D4, NOTE_G4,       0,       0,
  NOTE_G4, NOTE_G4, NOTE_F4, NOTE_D4, NOTE_C4,       0,       0,       0,

};


void Util::printArgs(const char * argTypes, ...) {
  va_list vl;
  va_start(vl, argTypes);

  for (int i = 0; argTypes[i] != '\0'; ++i) {
    union Printable_t {
         int     i;
         float   f;
         char    c;
         char   *s;
      } Printable;

      switch( argTypes[i] ) { 
         case 'i':
             Printable.i = va_arg(vl, int);
             Serial.print(Printable.i);
         break;

         case 'f':
             Printable.f = va_arg(vl, double);
             Serial.print(Printable.f);
         break;

         case 'c':
             Printable.c = va_arg(vl, int);
             Serial.print(Printable.c);
         break;

         case 's':
             Printable.s = va_arg(vl, char *);
             Serial.print(Printable.s);
         break;

         default:
             Serial.print(argTypes[i]);
         break;
      }
  }
  va_end(vl);
}

//ROAD
void Util::road(LedControl& lc) {
  int i = 0, j = 0;
  for (j = 0; j < 8; j++)
  {
    lc.setLed(0, 0, j, true);
    lc.setLed(0, 1, j, true);
    lc.setLed(0, 6, j, true);
    lc.setLed(0, 7, j, true);
  }

  for (i = 0; i <= 8; i++)
    for (j = 0; j < 8 + 3; j++)
    {
      lc.setLed(0, 3, j - 3, false);
      lc.setLed(0, 4, j - 3, false);
      lc.setLed(0, 3, j - 2, true);
      lc.setLed(0, 4, j - 2, true);
      lc.setLed(0, 3, j - 1, true);
      lc.setLed(0, 4, j - 1, true);
      lc.setLed(0, 3, j, true);
      lc.setLed(0, 4, j, true);
      delay(70);
    }
}

