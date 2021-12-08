#include "joystick.hpp"

const uint16_t Joystick::xThreshDefault        =  250;
const uint16_t Joystick::yThreshDefault        =  250;
const uint16_t Joystick::neutralJoyPosition    =  512;
const uint32_t Joystick::debounceDelayDefault  =  250;

Joystick::Joystick(const uint8_t& xInputPin, const uint8_t& yInputPin, const uint8_t& buttonInputPin,  \
                   const uint16_t& xThresh = xThreshDefault, const uint16_t& yThresh = yThreshDefault, \
                   const uint32_t& debounceTime = debounceDelayDefault)                                \
                   xPin(xInputPin), yPin(yInputPin), buttonPin(buttonInputPin),                        \
                   xInput(0), yInput(0), buttonPressed(false), debounceDelayTime(debounceTime)         \
                   xThreshold(xThresh), yThreshold(yThresh), lastPressTime(0),                         {

  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(buttonPin), handleButtonPressed(), FALLING);
}

void Joystick::update() {
  xInput = analogRead(xPin);
  yInput = analogRead(yPin);
  
  lastButtonState = buttonState;
  buttonState = digitalRead(buttonPin);



}

bool Joystick::debounceExpired() const { return (millis() - lastPressTime > debounceDelayTime); }
void Joystick::handleButtonPressed() { 
  if (debounceExpired()) {
    lastPressTime = millis();
    buttonPressed = true;
  }
}

bool Joystick::isButtonPressed() { return buttonPressed; }


const uint8_t Joystick::getHorizontalSense() {

}
