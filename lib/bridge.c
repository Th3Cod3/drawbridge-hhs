#include <avr/io.h>
#include "leds.h"
#include "bridge.h"
#include "servo.h"

void initBridge(){
    init_servo();
    DDRH |= _BV(MOTOR_IN1) | _BV(MOTOR_IN2);
}

void allBridgeLights(int status)
{
    setBridgeGreenTopLed(status);
    setBridgeGreenBottomLed(status);
    setBridgeRedBottomLed(status);
    setBridgeRedTopLed(status);
}

int bridgeControl(int status, int stepButton)
{
    setPanelCounterLed(status);
    switch (status)
    {
    case CHECK_FOR_BOAT_STATE:
        setTrafficLight(TRAFFIC_FREE);
        setBridgeLight(BOAT_STOP);
        // TODO: check for boat
        return 1 ? TRAFFIC_NOTIFICATION_STATE : CHECK_FOR_BOAT_STATE;
    case TRAFFIC_NOTIFICATION_STATE:
        setTrafficLight(TRAFFIC_NOTIFICATION);
        setBridgeLight(BOAT_STOP);
        // TODO: lock for a period with millis() of interrups
        return 1 ? STOP_TRAFFIC_STATE : TRAFFIC_NOTIFICATION_STATE;
    case STOP_TRAFFIC_STATE:
        setTrafficLight(TRAFFIC_STOP);
        barrierInstruction(BARRIER_CLOSED);
        // TODO: lock for a period with millis() of interrups
        return 1 ? OPEN_BRUG_STATE : STOP_TRAFFIC_STATE;
    case OPEN_BRUG_STATE:
        bridgeInstruction(BRIDGE_OPEN);
        // TODO: button press
        return 1 ? BOAT_FREE_STATE : OPEN_BRUG_STATE;
    case BOAT_FREE_STATE:
        bridgeInstruction(BRIDGE_STOP);
        setBridgeLight(BOAT_FREE);
        // TODO: timer || no boots
        return 1 ? BOAT_STOP_STATE : BOAT_FREE_STATE;
    case BOAT_STOP_STATE:
        setBridgeLight(BOAT_STOP);
        // TODO: timer
        return 1 ? CLOSE_BRUG_STATE : BOAT_STOP_STATE;
    case CLOSE_BRUG_STATE:
        bridgeInstruction(BRIDGE_CLOSE);
        // TODO: button press
        return 1 ? FREE_TRAFFIC_STATE : CLOSE_BRUG_STATE;
    case FREE_TRAFFIC_STATE:
        bridgeInstruction(BRIDGE_STOP);
        barrierInstruction(BARRIER_OPEN);
        // TODO: button press
        return 1 ? CHECK_FOR_BOAT_STATE : FREE_TRAFFIC_STATE;
    }

    return 0;
}

void setTrafficLight(int status)
{
    switch (status)
    {
    case TRAFFIC_STOP:
        setTrafficRedLed(ON);
        break;

    case TRAFFIC_FREE:
        setTrafficRedLed(OFF);
        break;

    case TRAFFIC_NOTIFICATION:
        // blink met millis();
        setTrafficRedLed(ON);
        break;
    }
}

void setBridgeLight(int status)
{
    switch (status)
    {
    case BOAT_STOP:
        setBridgeGreenTopLed(OFF);
        setBridgeGreenBottomLed(OFF);
        setBridgeYellowLed(ON);
        setBridgeRedBottomLed(ON);
        setBridgeRedTopLed(ON);
        break;

    case BOAT_FREE:
        setBridgeGreenTopLed(ON);
        setBridgeGreenBottomLed(ON);
        setBridgeYellowLed(OFF);
        setBridgeRedBottomLed(OFF);
        setBridgeRedTopLed(OFF);
        break;

    case BOAT_OPENING:
        setBridgeGreenTopLed(ON);
        setBridgeGreenBottomLed(ON);
        setBridgeYellowLed(OFF);
        setBridgeRedBottomLed(OFF);
        setBridgeRedTopLed(OFF);
        break;
    }
}

void bridgeInstruction(int status)
{
    switch (status)
    {
    case BRIDGE_CLOSE:
        PORTH |= _BV(MOTOR_IN1);
        PORTH &= ~_BV(MOTOR_IN2);
        break;

    case BRIDGE_OPEN:
        PORTH &= ~_BV(MOTOR_IN1);
        PORTH |= _BV(MOTOR_IN2);
        break;

    case BRIDGE_STOP:
        PORTH &= ~_BV(MOTOR_IN1);
        PORTH &= ~_BV(MOTOR_IN2);
        break;
    }
}

void barrierInstruction(int status)
{
    static lastStatus;
    switch (status)
    {
    case BARRIER_CLOSED:
        lastStatus = BARRIER_CLOSED;
        servo1_set_percentage(-100);
        servo2_set_percentage(-100);
        break;

    case BARRIER_OPEN:
        lastStatus = BARRIER_OPEN;
        servo1_set_percentage(100);
        servo2_set_percentage(100);
        break;

    case BARRIER_TOGGLE:
        lastStatus = !lastStatus;
        int value = lastStatus ? 100 : -100;
        servo1_set_percentage(value);
        servo2_set_percentage(value);
        break;
    }
}