/*
 * buttons.h
 * 
 * A push button Arduino library capable of returning the number of
 * consecutive button presses made in quick succession or if the 
 * button was held down for a long time. 
 * 
 * Based on LSC_Button by ben.jones12@gmail.com, forked from mdButton library
 * Based on mdPushButton by Michel Deslierres <sigmdel.ca/michel>
 * 
 */

#ifndef BUTTONS_H
#define BUTTONS_H

#include "Arduino.h"  // needed for platformIO

#define BUTTON_COUNT_MAX         20  // arbitrary max button amount - can be increased if needed

#define DEBOUNCE_PRESS_TIME      15  // delay to debounce the make part of the signal
#define DEBOUNCE_RELEASE_TIME    30  // delay to debounce the break part of the signal
#define MULTI_CLICK_TIME        250  // if 0, does not check for multiple button clicks
#define HOLD_TIME               500  // minimum time of button press for mdButton.status() to return a -1 (long button press)
                                     // all times in milliseconds
// Special state values
#define BUTTON_NO_STATE          0
#define BUTTON_HOLD_STATE       15

// Max number of clicks we support (won't report more even if button clicked more often)
#define BUTTON_MAX_CLICKS        5


typedef void (*buttonPressedCallback)(uint8_t, uint8_t);

enum buttonState_t { AWAIT_PRESS, DEBOUNCE_PRESS, AWAIT_RELEASE, DEBOUNCE_RELEASE, AWAIT_MULTI_PRESS };

union buttonData_t
{
  uint8_t _data;
  struct 
  {
    buttonState_t state  : 4;
    uint8_t clicks : 4;
  } data;
};


class multiButton {
  public:
    multiButton();  //constructor
    
    void setup(uint8_t id, uint8_t pin, uint8_t active = LOW, bool useInternalPullResistor = true); // setup input pin
   
    // Current library version
    int16_t version;

    void process();

    // Set callback function to be called when the button has been pressed   
    void onButtonPressed(buttonPressedCallback); // callback

   
  private:
    uint8_t _BUTTON_COUNT;                       // number of buttons actully connected / setup
    
    uint8_t _pin[BUTTON_COUNT_MAX];              // GPIO of digital button
    uint8_t _active[BUTTON_COUNT_MAX];           // state taht shows pressed button

    buttonPressedCallback _onButtonPressed;      // callback

    uint32_t _lastUpdateTime;                    // last update time for button states
    
    buttonData_t _buttonState[BUTTON_COUNT_MAX]; // data array for button states

    uint16_t _eventTime[BUTTON_COUNT_MAX];       // last update for a button
  
    uint8_t * _update();                         // checking button states and returning a value
};

class multiButtonWIFI {
  public:
    multiButtonWIFI();  //constructor
    
    void setup(uint8_t id, uint8_t active = LOW); // setup input pin

    void process();

    void update_button(uint8_t id, uint8_t state); // used to update the wifi state of a button

    // Set callback function to be called when the button has been pressed   
    void onButtonPressed(buttonPressedCallback); // callback
   
  private:
    uint8_t _BUTTON_COUNT;                       // number of buttons actully connected / setup
    
    uint8_t _pin[BUTTON_COUNT_MAX];              // state of WIFI button
    uint8_t _active[BUTTON_COUNT_MAX];           // state that shows pressed button

    buttonPressedCallback _onButtonPressed;      // callback

    uint32_t _lastUpdateTime;                    // last update time for button states
    
    buttonData_t _buttonState[BUTTON_COUNT_MAX]; // data array for button states

    uint16_t _eventTime[BUTTON_COUNT_MAX];       // last update for a button
  
    uint8_t * _update();                         // checking button states and returning a value
};

#endif
