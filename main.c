#ifndef __AVR_ATmega2560__
#define __AVR_ATmega2560__
#endif // !1 __AVR_ATmega2560__
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "lib/leds.h"
#include "lib/buttons.h"
#include "lib/bridge.h"

int main(void)
{
    initButtons();
    initLeds();
    initBridge();

    char step = 1;
    char mode = AUTOMATIC_MODE;
    barrierInstruction(BARRIER_OPEN);
    char barrierStatus = BARRIER_OPEN;
    char bridge = 0;
    while (1)
    {
        char emergencyButton = STATUS_EMERGENCY_BUTTON;
        char stepButton = STATUS_STEP_BUTTON;
        char modeButton = STATUS_MODE_BUTTON;
        char barrierButton = STATUS_BARRIER_BUTTON;
        char closedButton = STATUS_CLOSED_BUTTON;
        char openButton = STATUS_OPEN_BUTTON;
        char redLedsButton = STATUS_RED_LEDS_BUTTON;
        char yellowLedsButton = STATUS_YELLOW_LEDS_BUTTON;
        // int button8 = STATUS_PENDING_BUTTON;

        _delay_ms(10);

        if (emergencyButton)
        {
            mode = EMERGENCY_MODE;
        }
        else if (modeButton)
        {
            mode == AUTOMATIC_MODE
                ? MANUAL_MODE
                : AUTOMATIC_MODE;
        }

        if (mode == AUTOMATIC_MODE)
        {
            step = bridgeControl(step);
        }
        else if (mode == MANUAL_MODE)
        { //Knop2 ingedrukt = negeer cases
            if (stepButton)
            {
                step++;
            }

            if (barrierButton)
            { //Knop3 ingedrukt = Slagbomen open/dicht
                barrierInstruction(BARRIER_TOGGLE);
            }

            if (closedButton)
            { //Knop4 ingedrukt = dicht met dubbelrood
            }

            if (openButton)
            { //Knop5 ingedrukt = open met dubbelrood
            }

            if (redLedsButton)
            { //Knop6 ingedrukt = lampenrood
                setBridgeRedBottomLed(TOGGLE);
                setBridgeRedTopLed(TOGGLE);
            }

            if (yellowLedsButton)
            { //Knop7 ingedrukt = gelelamp aan
                setPanelYellow3Led(TOGGLE);
            }
        }
        _delay_ms(1000);
    }

    // BELANGRIJK KNOP 0,2,6 EN 7 MOETEN SCHAKELAARS ZIJN!!!
    return 0;
}
