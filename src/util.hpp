#include <stdarg.h>
#include <LedControl.h>
#include "menu.hpp"

#ifndef UTIL_HPP
#define UTIL_HPP

/* 
 * can't use enum class, because enums have to be converted
 * to uint8_t to use in pinMode functions
 */
namespace pincode {
  enum PinCode {
    
    /* lcd display pin codes */
    D4       =  4,
    D5       =  5,
    D6       =  6,
    D7       =  7,
    ENABLE   =  8,
    RS       = 13,
    CONTRAST =  9,

    /* led matrix pin codes */
    LOAD     = 10,
    CLK      = 11,
    DIN      = 12,

    /* joystick pin codes */
    VRX      = A0,
    VRY      = A1,
    SW       =  2

 };
}

namespace constants {
  /* number of MAX7221 drivers */
  const uint8_t DRIVER_NUM = 1;

  const uint8_t LCD_ROWS              =    2;
  const uint8_t LCD_COLS              =   16;
  const uint8_t LCD_CONTRAST_DEFAULT  =  100;
  
  const uint8_t LED_MATRIX_ROWS                = 8;
  const uint8_t LED_MATRIX_COLS                = 8;
  const uint8_t LED_MATRIX_CHIP                = 0;
  const uint8_t LED_MATRIX_BRIGHTNESS_DEFAULT  = 1;

  const uint8_t SLIDER_DELAY = 50;      /* slide delay */
  const uint8_t MAIN_MENU_SIZE = 3;     /* number of menu options */
  const Button mainMenuLayout[] = {
    Button("Play",    ButtonType::enterMenu),
    Button("Options", ButtonType::enterMenu),
    Button("About",   ButtonType::enterMenu)
  };
  const Button optionsMenuLayout[] = {
    Button("Back",       ButtonType::enterMenu, mainMenuLayout),
    Button("Contrast",   ButtonType::option),
    Button("Brightness", ButtonType::option),
    Button("Difficulty", ButtonType::option)
  };

}


namespace util {
  void printArgs(const char * argTypes, ...);
  void road(LedControl&);
}

#endif
