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
    DDRC &= ~_BV(MOTOR_CLOSE_BUTTON);
    PORTC |= _BV(MOTOR_OPEN_BUTTON) | _BV(MOTOR_CLOSE_BUTTON);
}

char readEmergencyButton()
{
    static char lastState;
    char state = STATUS_EMERGENCY_BUTTON;
    if (state && lastState != state)
    {
        return 1;
    }

    lastState = state;
    return 0;
};

char readStepButton()
{
    static char lastState;
    char state = STATUS_STEP_BUTTON;
    if (state && lastState != state)
    {
        return 1;
    }

    lastState = state;
    return 0;
};

char readModeButton()
{
    static char lastState;
    char state = STATUS_MODE_BUTTON;
    if (state && lastState != state)
    {
        return 1;
    }

    lastState = state;
    return 0;
};

char readBarrierButton()
{
    static char lastState;
    char state = STATUS_BARRIER_BUTTON;
    if (state && lastState != state)
    {
        return 1;
    }

    lastState = state;
    return 0;
};

char readClosedButton()
{
    static char lastState;
    char state = STATUS_CLOSED_BUTTON;
    if (state && lastState != state)
    {
        return 1;
    }

    lastState = state;
    return 0;
};

char readOpenButton()
{
    static char lastState;
    char state = STATUS_OPEN_BUTTON;
    if (state && lastState != state)
    {
        return 1;
    }

    lastState = state;
    return 0;
};

char readRedLedsButton()
{
    static char lastState;
    char state = STATUS_RED_LEDS_BUTTON;
    if (state && lastState != state)
    {
        return 1;
    }

    lastState = state;
    return 0;
};

char readYellowLedsButton()
{
    static char lastState;
    char state = STATUS_YELLOW_LEDS_BUTTON;
    if (state && lastState != state)
    {
        return 1;
    }

    lastState = state;
    return 0;
};
