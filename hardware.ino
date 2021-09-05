/*
 * Hardware related stuff
 */

#include <Bounce.h>

// Define button pins
#define BTN_EMPTY_NOTE 2

// Button debounce
static Bounce bounce_empty_note = Bounce(BTN_EMPTY_NOTE, DEBOUNCE_TIME);

/* Check if the button went from a HIGH to LOW state */
bool hardware_check_button(byte key)
{
    Bounce *b;

    if (key == BTN_EMPTY_NOTE)
        b = &bounce_empty_note;

    return (b->update() && b->fallingEdge());
}

void hardware_init()
{
    pinMode(BTN_EMPTY_NOTE, INPUT_PULLUP);
}
