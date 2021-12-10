#include <stdint.h>
#include "Arduino.h"

#ifndef JOYSTICK_HPP
#define JOYSTICK_HPP

/* lower if lower thresh reached
 * upper if upper thresh reached
 * neutral if in between
 * enum class used to determine in which sense
 * the joystick was moved
 */
enum class JoystickSense {
  neutral,
  upper,
  lower
};

class Joystick {
  /* MEMBERS */
  private:
    uint8_t  xPin;
    uint8_t  yPin;
    uint8_t  buttonPin;

    uint16_t       xInput;
    uint16_t       yInput;
    bool           buttonPressed;
    bool           buttonState;
    bool           lastButtonState;

    uint16_t xThreshold;
    uint16_t yThreshold;
    uint32_t debounceDelayTime;
    uint32_t lastPressTime;


  public:
    /* default values */
    static const uint16_t xThreshDefault;
    static const uint16_t yThreshDefault;
    static const uint16_t neutralJoyPosition;
    static const uint32_t debounceDelayDefault;


  /* METHODS */
  private:
    bool debounceExpired() const;
    JoystickSense getSense(const uint16_t&, const uint16_t&) const;
    void resetButtonPressed();
    void handleButtonPressed();    
    
  public:
    Joystick(const uint8_t&, const uint8_t&, const uint8_t&, const uint16_t& = Joystick::xThreshDefault, const uint16_t& = Joystick::yThreshDefault, const uint32_t& = Joystick::debounceDelayDefault);
    
    void update();

    JoystickSense getVerticalSense()   const;
    JoystickSense getHorizontalSense() const;

    bool isButtonPressed() const;
    bool getButtonState()  const;
};

#endif
