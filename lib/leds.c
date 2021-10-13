#include <avr/io.h>
#include "leds.h"

// configure led pins as output
void initLeds(void)
{
    // PORTA
    DDRA |= _BV(EMERGENCY_LED);
    DDRA |= _BV(PANEL_BRIDGE_OPEN_LED);
    DDRA |= _BV(PANEL_BRIDGE_CLOSED_LED);
    DDRA |= _BV(PANEL_MODE_LED);
    DDRA |= _BV(PANEL_BARRIER_LED);
    DDRA |= _BV(PANEL_BRIDGE_RED_LED);
    DDRA |= _BV(PANEL_YELLOW_1_LED);
    DDRA |= _BV(PANEL_YELLOW_2_LED);

    // PORTB
    DDRB |= _BV(PANEL_COUNTER_1_LED);
    DDRB |= _BV(PANEL_COUNTER_2_LED);
    DDRB |= _BV(PANEL_COUNTER_3_LED);
    DDRB |= _BV(PANEL_COUNTER_4_LED);

    // PORTL
    DDRL |= _BV(BRIDGE_GREEN_TOP_LED);
    DDRL |= _BV(BRIDGE_RED_TOP_LED);
    DDRL |= _BV(BRIDGE_GREEN_BOTTOM_LED);
    DDRL |= _BV(BRIDGE_RED_BOTTOM_LED);
    DDRL |= _BV(BRIDGE_YELLOW_LED);
    DDRL |= _BV(TAFFIC_RED_LED);

    // PORTE
    DDRE |= _BV(PANEL_YELLOW_3_LED);

    // PORTK
    DDRK |= _BV(PANEL_YELLOW_4_LED);
}

void setEmergencyLed(int status)
{
    if (status == ON)
    {
        PORTA |= _BV(EMERGENCY_LED);
    }
    else if (status == TOGGLE)
    {
        PORTA ^= _BV(EMERGENCY_LED);
    }
    else if (status == OFF)
    {
        PORTA &= ~_BV(EMERGENCY_LED);
    }
}

void setBridgeRedBottomLed(int status)
{
    if (status == ON)
    {
        PORTL |= _BV(BRIDGE_RED_BOTTOM_LED);
    }
    else if (status == TOGGLE)
    {
        PORTL ^= _BV(BRIDGE_RED_BOTTOM_LED);
    }
    else if (status == OFF)
    {
        PORTL &= ~_BV(BRIDGE_RED_BOTTOM_LED);
    }
}

void setBridgeRedTopLed(int status)
{
    if (status == ON)
    {
        PORTL |= _BV(BRIDGE_RED_TOP_LED);
    }
    else if (status == TOGGLE)
    {
        PORTL ^= _BV(BRIDGE_RED_TOP_LED);
    }
    else if (status == OFF)
    {
        PORTL &= ~_BV(BRIDGE_RED_TOP_LED);
    }
}

void setPanelBridgeClosedLed(int status)
{
    if (status == ON)
    {
        PORTA |= _BV(PANEL_BRIDGE_CLOSED_LED);
    }
    else if (status == TOGGLE)
    {
        PORTA ^= _BV(PANEL_BRIDGE_CLOSED_LED);
    }
    else if (status == OFF)
    {
        PORTA &= ~_BV(PANEL_BRIDGE_CLOSED_LED);
    }
}

void setPanelBarrierLed(int status)
{
    if (status == ON)
    {
        PORTA |= _BV(PANEL_BARRIER_LED);
    }
    else if (status == TOGGLE)
    {
        PORTA ^= _BV(PANEL_BARRIER_LED);
    }
    else if (status == OFF)
    {
        PORTA &= ~_BV(PANEL_BARRIER_LED);
    }
}

void setPanelBridgeRedLed(int status) // TODO: to be used
{
    if (status == ON)
    {
        PORTA |= _BV(PANEL_BRIDGE_RED_LED);
    }
    else if (status == TOGGLE)
    {
        PORTA ^= _BV(PANEL_BRIDGE_RED_LED);
    }
    else if (status == OFF)
    {
        PORTA &= ~_BV(PANEL_BRIDGE_RED_LED);
    }
}

void setPanelYellow1Led(int status) // TODO: to be used
{
    if (status == ON)
    {
        PORTA |= _BV(PANEL_YELLOW_1_LED);
    }
    else if (status == TOGGLE)
    {
        PORTA ^= _BV(PANEL_YELLOW_1_LED);
    }
    else if (status == OFF)
    {
        PORTA &= ~_BV(PANEL_YELLOW_1_LED);
    }
}

void setPanelYellow2Led(int status) // TODO: to be used
{
    if (status == ON)
    {
        PORTA |= _BV(PANEL_YELLOW_2_LED);
    }
    else if (status == TOGGLE)
    {
        PORTA ^= _BV(PANEL_YELLOW_2_LED);
    }
    else if (status == OFF)
    {
        PORTA &= ~_BV(PANEL_YELLOW_2_LED);
    }
}

void setPanelYellow3Led(int status)
{
    if (status == ON)
    {
        PORTE |= _BV(PANEL_YELLOW_3_LED);
    }
    else if (status == TOGGLE)
    {
        PORTE ^= _BV(PANEL_YELLOW_3_LED);
    }
    else if (status == OFF)
    {
        PORTE &= ~_BV(PANEL_YELLOW_3_LED);
    }
}

void setPanelCounterLed(int number)
{
    PORTB = 0;
    if (number <= 0x0F)
    {
        PORTB |= number;
    }
}

void setPanelModeLed(int status) // TODO: to be used
{
    if (status == ON)
    {
        PORTA |= _BV(PANEL_MODE_LED);
    }
    else if (status == TOGGLE)
    {
        PORTA ^= _BV(PANEL_MODE_LED);
    }
    else if (status == OFF)
    {
        PORTA &= ~_BV(PANEL_MODE_LED);
    }
}

void setBridgeYellowLed(int status)
{
    if (status == ON)
    {
        PORTL |= _BV(BRIDGE_YELLOW_LED);
    }
    else if (status == TOGGLE)
    {
        PORTL ^= _BV(BRIDGE_YELLOW_LED);
    }
    else if (status == OFF)
    {
        PORTL &= ~_BV(BRIDGE_YELLOW_LED);
    }
}

void setTrafficRedLed(int status)
{
    if (status == ON)
    {
        PORTL |= _BV(TAFFIC_RED_LED);
    }
    else if (status == TOGGLE)
    {
        PORTL ^= _BV(TAFFIC_RED_LED);
    }
    else if (status == OFF)
    {
        PORTL &= ~_BV(TAFFIC_RED_LED);
    }
}

void setBridgeGreenTopLed(int status)
{
    if (status == ON)
    {
        PORTL |= _BV(BRIDGE_GREEN_TOP_LED);
    }
    else if (status == TOGGLE)
    {
        PORTL ^= _BV(BRIDGE_GREEN_TOP_LED);
    }
    else if (status == OFF)
    {
        PORTL &= ~_BV(BRIDGE_GREEN_TOP_LED);
    }
}

void setBridgeGreenBottomLed(int status)
{
    if (status == ON)
    {
        PORTL |= _BV(BRIDGE_GREEN_BOTTOM_LED);
    }
    else if (status == TOGGLE)
    {
        PORTL ^= _BV(BRIDGE_GREEN_BOTTOM_LED);
    }
    else if (status == OFF)
    {
        PORTL &= ~_BV(BRIDGE_GREEN_BOTTOM_LED);
    }
}

void setPanelBridgeOpenLed(int status)
{
    if (status == ON)
    {
        PORTA |= _BV(PANEL_BRIDGE_OPEN_LED);
    }
    else if (status == TOGGLE)
    {
        PORTA ^= _BV(PANEL_BRIDGE_OPEN_LED);
    }
    else if (status == OFF)
    {
        PORTA &= ~_BV(PANEL_BRIDGE_OPEN_LED);
    }
}