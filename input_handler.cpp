#include "input_handler.h"

static const uint8_t all_buttons[] = { LEFT_BUTTON, RIGHT_BUTTON, UP_BUTTON, DOWN_BUTTON, A_BUTTON, B_BUTTON };

static unsigned int index_for_button(uint8_t button) {
    unsigned int index = 0;
    while (all_buttons[index] != button && index < NUM_BUTTONS) index++;

    return index;
}

InputHandler::InputHandler()
{
    const unsigned long now = millis();
    for (unsigned int button_idx = 0; button_idx < NUM_BUTTONS; button_idx++) {
        _last_seen_state[button_idx] = false;
        _last_seen_time[button_idx] = now;
    }
}

unsigned long InputHandler::last_time_for_button(uint8_t button)
{
    unsigned int index = index_for_button(button);
    return _last_seen_time[index];
}

bool InputHandler::last_state_for_button(uint8_t button)
{
    unsigned int index = index_for_button(button);
    return _last_seen_state[index];
}

void InputHandler::handle_input(Arduboy& adb)
{
    const unsigned long now = millis();
    for (unsigned int button_idx = 0; button_idx < NUM_BUTTONS; button_idx++) {
        uint8_t button = all_buttons[button_idx];

        bool last_state = last_state_for_button(button);
        unsigned long last_time = last_time_for_button(button);

        bool down = adb.pressed(button);

        if (down != last_state) {
            if ( (now - last_time) > repeat_rate ) {
                button_handler(button, down);

                _last_seen_state[button_idx] = down;
                _last_seen_time[button_idx] = now;
            }
        }
    }

}
