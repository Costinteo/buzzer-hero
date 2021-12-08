#include <stdarg.h>
#include <LedControl.h>

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
    DIN      = 12

 };
}

namespace constants {
  /* number of MAX7221 drivers */
  const uint8_t DRIVER_NUM = 1;

  const uint8_t LCD_ROWS = 2;
  const uint8_t LCD_COLS = 16;
  
  const uint8_t LED_MATRIX_ROWS        = 8;
  const uint8_t LED_MATRIX_COLS        = 8;
  const uint8_t LED_MATRIX_CHIP        = 0;
  const uint8_t LED_MATRIX_BRIGHTNESS  = 1;
}

namespace util {
  void printArgs(const char * argTypes, ...);
  void road(LedControl&);
}

#endif