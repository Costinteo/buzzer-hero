#include "joystick.hpp"

const uint16_t Joystick::xThreshDefault        =  250;
const uint16_t Joystick::yThreshDefault        =  250;
const uint16_t Joystick::neutralJoyPosition    =  512;
const uint32_t Joystick::debounceDelayDefault  =  250;

Joystick::Joystick(const uint8_t& xInputPin, const uint8_t& yInputPin, const uint8_t& buttonInputPin,  \
                   const uint16_t& xThresh, const uint16_t& yThresh, const uint32_t& debounceTime) :   \
                   xPin(xInputPin), yPin(yInputPin), buttonPin(buttonInputPin), xInput(0), yInput(0),  \
                   buttonPressed(false), debounceDelayTime(debounceTime), lastPressTime(0),            \
                   xThreshold(xThresh), yThreshold(yThresh), buttonState(HIGH), lastButtonState(HIGH)  {

  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);

}

void Joystick::update() {
  
  resetButtonPressed();

  xInput = analogRead(xPin);
  yInput = analogRead(yPin);
 
  lastButtonState = buttonState;
  buttonState = digitalRead(buttonPin);
  handleButtonPressed();

}

bool Joystick::debounceExpired() const { return (millis() - lastPressTime > debounceDelayTime); }
void Joystick::resetButtonPressed() { buttonPressed ^= buttonPressed; }
void Joystick::handleButtonPressed() { 
  /* because input for button is PULLUP, !buttonState means it's being pressed */
  if (debounceExpired() && !buttonState && lastButtonState) {
    lastPressTime = millis();
    buttonPressed = true;
  }
}


JoystickSense Joystick::getSense(const uint16_t& input, const uint16_t& threshold) const {
  uint16_t upperThreshold = Joystick::neutralJoyPosition + threshold;
  uint16_t lowerThreshold = Joystick::neutralJoyPosition - threshold;
  
  if (input > upperThreshold) return JoystickSense::upper;
  if (input < lowerThreshold) return JoystickSense::lower;
  return JoystickSense::neutral;
}

JoystickSense Joystick::getVerticalSense() const { return getSense(yInput, yThreshold); }
JoystickSense Joystick::getHorizontalSense() const { return getSense(xInput, xThreshold); }

bool Joystick::isButtonPressed() const { return buttonPressed; }
bool Joystick::getButtonState()  const { return buttonState;   }

