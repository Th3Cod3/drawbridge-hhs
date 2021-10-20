#include <avr/io.h>
#include "buttons.h"

// configure button pins as input
void initButtons(void)
{
    DDRA &= ~_BV(EMERGENCY_BUTTON);
    DDRA &= ~_BV(STEP_BUTTON);
    DDRA &= ~_BV(MODE_BUTTON);
    DDRA &= ~_BV(BARRIER_BUTTON);
    DDRA &= ~_BV(CLOSED_BUTTON);
    DDRA &= ~_BV(OPEN_BUTTON);
    DDRA &= ~_BV(RED_LEDS_BUTTON);
    DDRA &= ~_BV(YELLOW_LEDS_BUTTON);
    PORTA = 0xFF;
    DDRC &= ~_BV(MOTOR_OPEN_BUTTON);
}
