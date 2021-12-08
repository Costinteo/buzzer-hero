#ifndef JOYSTICK_HPP
#define JOYSTICK_HPP

class Joystick {
  /* MEMBERS */
  private:
    uint8_t  xPin;
    uint8_t  yPin;
    uint8_t  buttonPin;

    uint16_t       xInput;
    uint16_t       yInput;
    volatile bool  buttonPressed;

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
    uint8_t getSense(const uint16_t&) const;
    void handleButtonPressed();    

  public:
    Joystick(const uint8_t&, const uint8_t&, const uint8_t&, const uint16_t&, const uint16_t&, const uint32_t&);
    
    void update();

    uint8_t getVerticalSense()   const;
    uint8_t getHorizontalSense() const;


    bool isButtonPressed() const;

}

#endif
