#ifndef UTIL_HPP
#define UTIL_HPP

#include <stdarg.h>
#include <stdint.h>
#include <LedControl.h>
#include "menu.hpp"

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

/*
 * The global variables referred throughout the program are stored in this class
 * After days spent thinking of what is causing preprocessor issues
 * I've decided to try putting them in a class instead of a namespace
 * Apparently this has tempered the compiler and at a superficial level it seems to work
 * I am almost certain the compiler completely ignores my header guards
 */
class Util {
  public:
    static const uint8_t DRIVER_NUM = 1;

    static const uint8_t LCD_ROWS              =    2;
    static const uint8_t LCD_COLS              =   16;
    static const uint8_t LCD_CONTRAST_DEFAULT  =  100;
    
    static const uint8_t LED_MATRIX_ROWS                = 8;
    static const uint8_t LED_MATRIX_COLS                = 8;
    static const uint8_t LED_MATRIX_CHIP                = 0;
    static const uint8_t LED_MATRIX_BRIGHTNESS_DEFAULT  = 1;

    static const uint8_t SLIDER_DELAY = 50;      /* slide delay */

    static const uint8_t MAIN_MENU_SIZE = 3;
    static Button mainMenuButtonArray[];
    static const Layout mainMenuLayout;

    static const uint8_t PLAY_MENU_SIZE = 1;
    static Button playMenuButtonArray[];
    static const Layout playMenuLayout;

    static const uint8_t OPTIONS_MENU_SIZE = 4;
    static Button optionsMenuButtonArray[]; 
    static const Layout optionsMenuLayout;

    static const uint8_t ABOUT_MENU_SIZE = 4;
    static Button aboutMenuButtonArray[];
    static const Layout aboutMenuLayout;
    
    static void linkMenuPointers(const uint8_t&, ...);
    static void printArgs(const char * argTypes, ...);
    static void road(LedControl&);

};

#endif
