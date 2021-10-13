#include <avr/io.h>
#include "buttons.h"

// configure button pins as input
void initButtons(void)
{
    DDRF &= ~_BV(EMERGENCY_BUTTON);
    DDRF &= ~_BV(STEP_BUTTON);
    DDRF &= ~_BV(MODE_BUTTON);
    DDRF &= ~_BV(BARRIER_BUTTON);
    DDRF &= ~_BV(CLOSED_BUTTON);
    DDRF &= ~_BV(OPEN_BUTTON);
    DDRF &= ~_BV(RED_LEDS_BUTTON);
    DDRF &= ~_BV(YELLOW_LEDS_BUTTON);
    DDRK &= ~_BV(PENDING_BUTTON); //NR8 (staat een boot voor de brug lampje aan op paneel)
}
