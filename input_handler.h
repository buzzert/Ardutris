#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <Arduboy.h>
#include "utils.h"

#define NUM_BUTTONS 6

class InputHandler
{
public:
    InputHandler();

    // Call this in the main runloop
    void handle_input(Arduboy& adb);

    unsigned long repeat_rate = 200;
    void(*button_handler)(uint8_t button, bool down) = NULL;

private:
    bool          _last_seen_state[NUM_BUTTONS];
    unsigned long _last_seen_time[NUM_BUTTONS];

    bool          last_state_for_button(uint8_t button);
    unsigned long last_time_for_button(uint8_t button);

};

#endif
