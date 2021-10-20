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
    barrierInstruction(BARRIER_OPEN);
    char step = 0;
    char mode = MANUAL_MODE;
    char barrierStatus = BARRIER_OPEN;
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
        // int button8 = STATUS_MOTOR_OPEN_BUTTON;
        _delay_ms(10);

        if (emergencyButton)
        {
            setEmergencyLed(ON);
            bridgeInstruction(BRIDGE_STOP);
            setTrafficLight(TRAFFIC_STOP);
            setBridgeLight(BOAT_STOP);
            mode = EMERGENCY_MODE;
        }
        else if (modeButton)
        {
            setEmergencyLed(OFF);
            if (mode == AUTOMATIC_MODE)
            {
                setPanelModeLed(ON);
                setPanelCounterLed(OFF);
                mode = MANUAL_MODE;
            }
            else
            {
                setPanelModeLed(OFF);
                mode = AUTOMATIC_MODE;
            }
        }

        if (mode == AUTOMATIC_MODE)
        {
            step = bridgeControl(step, stepButton);
        }
        else if (mode == MANUAL_MODE)
        {

            if (barrierButton)
            {
                barrierInstruction(BARRIER_TOGGLE);
            }

            if (closedButton)
            {
                bridgeInstruction(BRIDGE_CLOSE);
            }

            if (openButton)
            {
                bridgeInstruction(BRIDGE_OPEN);
                setBridgeLight(BOAT_STOP);
            }

            if (redLedsButton)
            {
                setBridgeRedBottomLed(TOGGLE);
                setBridgeRedTopLed(TOGGLE);
                setTrafficRedLed(TOGGLE);
            }

            if (yellowLedsButton)
            {
                setBridgeYellowLed(TOGGLE);
            }
        }
        _delay_ms(500); // only for debuggen
    }

    // BELANGRIJK KNOP 0,2,6 EN 7 MOETEN SCHAKELAARS ZIJN!!!
    return 0;
}
