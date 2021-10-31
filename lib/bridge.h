#ifndef BRIDGE_LIB
#define BRIDGE_LIB
// PINS
#define MOTOR_IN1 PH4
#define MOTOR_IN2 PH5

// SETTINGS
#define TIMER_TRAFFIC_NOTIFICATION 2000   // ms
#define DELAY_AFTER_BARRIER 2000          // ms
#define DELAY_TO_KEEP_BRIDGE_OPEN 4000    // ms
#define TIMER_TO_START_CLOSED_BRIDGE 1000 // ms

// BRIDGE MODES
#define AUTOMATIC_MODE 0
#define MANUAL_MODE 1
#define EMERGENCY_MODE 2

// TRAFFIC LIGHT ACTIONS
#define TRAFFIC_STOP 0
#define TRAFFIC_FREE 1
#define TRAFFIC_NOTIFICATION 2

// BRIDGE ACTIONS
#define BRIDGE_CLOSE 0
#define BRIDGE_OPEN 1
#define BRIDGE_STOP 2
#define BRIDGE_CHECK 3

// BARRIER ACTIONS
#define BARRIER_CLOSED 0
#define BARRIER_OPEN 1
#define BARRIER_TOGGLE 2

// BRIDGE STATES
#define CHECK_FOR_BOAT_STATE 0
#define TRAFFIC_NOTIFICATION_STATE 1
#define STOP_TRAFFIC_STATE 2
#define OPEN_BRUG_STATE 3
#define BOAT_FREE_STATE 4
#define BOAT_STOP_STATE 5
#define CLOSE_BRUG_STATE 6
#define FREE_TRAFFIC_STATE 7

// BOAT TRAFFIC LIGHT ACTIONS
#define BOAT_STOP 0
#define BOAT_FREE 1

void initBridge();

void allBridgeLights(int status);

// @return nextStep
int bridgeControl(int status, int stepButton);

void setTrafficLight(int status);

void setBridgeLight(int status);

void bridgeInstruction(int status);

void barrierInstruction(int status);

#endif // !BRIDGE_LIB