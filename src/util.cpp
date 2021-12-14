#include "util.hpp"

/*
void constants::makeLinks(Button * layout, const uint8_t& size, ...) {
  va_list vl;
  va_start(vl, size);

  for (uint8_t i = 0; i < size; i++) {
    Button& bt = layout[i];
    switch (bt.bType) {
      case ButtonType::enterMenu:
        bt.bAction.menuToEnter = va_arg(vl, Button *);
        break;
      case ButtonType::option:
        bt.bAction.valueToChange = va_arg(vl, uint8_t *);
        break;
      case ButtonType::info:
        bt.bAction.infoToPrint = va_arg(vl, const char *);
    }
  }

  va_end(vl);

}
*/
void util::printArgs(const char * argTypes, ...) {
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
void util::road(LedControl& lc) {
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

