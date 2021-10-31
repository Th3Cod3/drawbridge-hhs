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
    setBridgeLight(BOAT_STOP);
    setTrafficLight(TRAFFIC_STOP);
    barrierInstruction(BARRIER_OPEN);
    char step = 0;
    char mode = MANUAL_MODE;
    char motorStatus = BRIDGE_STOP;
    while (1)
    {
        char emergencyButton = readEmergencyButton();
        char stepButton = readStepButton();
        char modeButton = readModeButton();
        char barrierButton = readBarrierButton();
        char closedButton = readClosedButton();
        char openButton = readOpenButton();
        char redLedsButton = readRedLedsButton();
        char yellowLedsButton = readYellowLedsButton();
        char motorOpenButton = STATUS_MOTOR_OPEN_BUTTON;
        char motorCloseButton = STATUS_MOTOR_CLOSE_BUTTON;
        _delay_ms(10);

        if (emergencyButton && mode != EMERGENCY_MODE)
        {
            setEmergencyLed(ON);
            bridgeInstruction(BRIDGE_STOP);
            setTrafficLight(TRAFFIC_STOP);
            setBridgeLight(BOAT_STOP);
            mode = EMERGENCY_MODE;
        }
        else if (emergencyButton && mode == EMERGENCY_MODE)
        {
            setEmergencyLed(OFF);
            mode = MANUAL_MODE;
        }
        else if (modeButton && mode != EMERGENCY_MODE)
        {
            setEmergencyLed(OFF);
            bridgeInstruction(BRIDGE_STOP);
            setTrafficLight(TRAFFIC_STOP);
            setBridgeLight(BOAT_STOP);
            if (mode == AUTOMATIC_MODE)
            {
                setPanelCounterLed(OFF);
                mode = MANUAL_MODE;
            }
            else
            {
                mode = AUTOMATIC_MODE;
            }
        }

        if (mode == AUTOMATIC_MODE)
        {
            setPanelModeLed(OFF);
            step = bridgeControl(step, stepButton);
        }
        else if (mode == MANUAL_MODE)
        {
            setPanelModeLed(ON);
            if (barrierButton)
            {
                barrierInstruction(BARRIER_TOGGLE);
            }

            if (motorStatus == BRIDGE_OPEN && motorOpenButton)
            {
                bridgeInstruction(BRIDGE_STOP);
                setPanelBridgeOpenLed(ON);
                motorStatus = BRIDGE_STOP;
            }
            else if (motorStatus == BRIDGE_CLOSE && motorCloseButton)
            {
                setPanelBridgeClosedLed(ON);
                bridgeInstruction(BRIDGE_STOP);
                motorStatus = BRIDGE_STOP;
            }
            else if (closedButton && !motorCloseButton)
            {
                setPanelBridgeOpenLed(OFF);
                bridgeInstruction(BRIDGE_CLOSE);
                motorStatus = BRIDGE_CLOSE;
            }
            else if (openButton && !motorOpenButton)
            {
                setPanelBridgeClosedLed(OFF);
                bridgeInstruction(BRIDGE_OPEN);
                setBridgeLight(BOAT_STOP);
                motorStatus = BRIDGE_OPEN;
            }

            if (redLedsButton)
            {
                setPanelBridgeRedLed(TOGGLE);
                setBridgeRedBottomLed(TOGGLE);
                setBridgeRedTopLed(TOGGLE);
                setTrafficRedLed(TOGGLE);
            }

            if (yellowLedsButton)
            {
                setBridgeYellowLed(TOGGLE);
            }
        }
    }

    return 0;
}
