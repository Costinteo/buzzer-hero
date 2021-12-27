# Buzzer Hero

Work-in-progress led matrix game, inspired by Guitar Hero. I'm using an Arduino Uno board. Hopefully, it'll be as fun as I imagine it.

Update: It was NOT fun. Besides not being fun, I also abandoned it mid-way out of frustration and tiredness. Happens, I guess.

## System Architecture

The system was designed in the following way:

```
Game
 |
 |
 -- LCD
 |
 -- LED_MATRIX
 |
 -- Joystick
 |
 -- Menu
     |
     -- Buttons
```

A Game class would contain an LCD, an LED Matrix, a Joystick and a Menu. LCD and LED Matrix were taken straight from the LiquidCrystal and LedControl libraries. Joystick and Menu were written manually by me.

The Joystick class should ease the use of Joysticks, simplifying inputs down to different "senses" of travel. For example, if the sense for an axis is "upper", that means it is going towards the upper threshold, surpassing it. 

The Menu class is merely a way of holding data together. The whole interaction with the menu data is to be done manually in the Game class, interfacting the input method (in our case, a joystick) with the Menu data, given the methods implemented in the Menu class.


