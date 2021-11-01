#include <avr/io.h>
#include "leds.h"
#include "buttons.h"
#include "bridge.h"
#include "servo.h"

void initBridge()
{
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

int bridgeControl(int status, int timer)
{
    setPanelCounterLed(status);
    switch (status)
    {
    case CHECK_FOR_BOAT_STATE:
        setTrafficLight(TRAFFIC_FREE);
        setBridgeLight(BOAT_SMALL_FREE);
        // TODO: check for boat
        return STATUS_STEP_BUTTON ? TRAFFIC_NOTIFICATION_STATE : CHECK_FOR_BOAT_STATE;
    case TRAFFIC_NOTIFICATION_STATE:
        setTrafficLight(TRAFFIC_NOTIFICATION);
        setBridgeLight(BOAT_STOP);
        // TODO: lock for a period with millis() of interrups
        if (timer > TIMER_TRAFFIC_NOTIFICATION / 10)
        {
            return STOP_TRAFFIC_STATE;
        }
        else
        {
            timer = 0;
            return TRAFFIC_NOTIFICATION_STATE;
        }
    case STOP_TRAFFIC_STATE:
        setTrafficLight(TRAFFIC_STOP);
        barrierInstruction(BARRIER_CLOSED);
        // TODO: lock for a period with millis() of interrups
        if (timer > DELAY_AFTER_BARRIER / 10)
        {
            return OPEN_BRUG_STATE;
        }
        else
        {
            timer = 0;
            return STOP_TRAFFIC_STATE;
        }
    case OPEN_BRUG_STATE:
        if (STATUS_MOTOR_OPEN_BUTTON)
        {
            bridgeInstruction(BRIDGE_STOP);
            return BOAT_FREE_STATE;
        }
        else
        {
            bridgeInstruction(BRIDGE_OPEN);
            return OPEN_BRUG_STATE;
        }
    case BOAT_FREE_STATE:
        bridgeInstruction(BRIDGE_STOP);
        setBridgeLight(BOAT_FREE);
        // TODO: timer || no boots
        if (timer > DELAY_TO_KEEP_BRIDGE_OPEN / 10)
        {
            return BOAT_STOP_STATE;
        }
        else
        {
            timer = 0;
            return BOAT_FREE_STATE;
        }
    case BOAT_STOP_STATE:
        setBridgeLight(BOAT_STOP);
        if (timer > TIMER_TO_START_CLOSED_BRIDGE / 10)
        {
            return CLOSE_BRUG_STATE;
        }
        else
        {
            timer = 0;
            return BOAT_STOP_STATE;
        }
    case CLOSE_BRUG_STATE:
        bridgeInstruction(BRIDGE_CLOSE);
        if (STATUS_MOTOR_CLOSE_BUTTON)
        {
            bridgeInstruction(BRIDGE_STOP);
            return FREE_TRAFFIC_STATE;
        }
        else
        {
            bridgeInstruction(BRIDGE_CLOSE);
            return CLOSE_BRUG_STATE;
        }
    case FREE_TRAFFIC_STATE:
        setBridgeLight(BOAT_SMALL_FREE);
        bridgeInstruction(BRIDGE_STOP);
        barrierInstruction(BARRIER_OPEN);
        if (timer > DELAY_AFTER_BARRIER / 10)
        {
            return CHECK_FOR_BOAT_STATE;
        }
        else
        {
            timer = 0;
            return FREE_TRAFFIC_STATE;
        }
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
        // TODO: blink met millis();
        setTrafficLight(TRAFFIC_STOP);
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
        setBridgeYellowLed(OFF);
        setBridgeRedBottomLed(ON);
        setBridgeRedTopLed(ON);
        setPanelBridgeRedLed(ON);
        break;

    case BOAT_FREE:
        setBridgeGreenTopLed(ON);
        setBridgeGreenBottomLed(ON);
        setBridgeYellowLed(OFF);
        setBridgeRedBottomLed(OFF);
        setBridgeRedTopLed(OFF);
        setPanelBridgeRedLed(OFF);
        break;

    case BOAT_SMALL_FREE:
        setBridgeGreenTopLed(OFF);
        setBridgeGreenBottomLed(OFF);
        setBridgeYellowLed(OFF);
        setBridgeRedBottomLed(ON);
        setBridgeRedTopLed(ON);
        setPanelBridgeRedLed(ON);
        break;
    }
}

void bridgeInstruction(int status)
{
    switch (status)
    {
    case BRIDGE_CLOSE:
        if (STATUS_MOTOR_CLOSE_BUTTON)
            return bridgeInstruction(BRIDGE_STOP);
        PORTH |= _BV(MOTOR_IN1);
        PORTH &= ~_BV(MOTOR_IN2);
        return;

    case BRIDGE_OPEN:
        if (STATUS_MOTOR_OPEN_BUTTON)
            return bridgeInstruction(BRIDGE_STOP);
        PORTH &= ~_BV(MOTOR_IN1);
        PORTH |= _BV(MOTOR_IN2);
        return;

    case BRIDGE_CHECK:
        PORTH &= ~_BV(MOTOR_IN1);
        PORTH &= ~_BV(MOTOR_IN2);
        return;

    case BRIDGE_STOP:
        PORTH &= ~_BV(MOTOR_IN1);
        PORTH &= ~_BV(MOTOR_IN2);
        return;
    }
}

void barrierInstruction(int status)
{
    static char lastStatus;
    switch (status)
    {
    case BARRIER_CLOSED:
        setPanelBarrierLed(ON);
        lastStatus = BARRIER_CLOSED;
        servo1_set_percentage(-100);
        servo2_set_percentage(-100);
        return;

    case BARRIER_OPEN:
        setPanelBarrierLed(OFF);
        lastStatus = BARRIER_OPEN;
        servo1_set_percentage(100);
        servo2_set_percentage(100);
        return;

    case BARRIER_TOGGLE:
        lastStatus = !lastStatus;
        lastStatus ? barrierInstruction(BARRIER_OPEN) : barrierInstruction(BARRIER_CLOSED);
        return;
    }
}