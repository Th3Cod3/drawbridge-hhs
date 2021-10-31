#ifndef BUTTONS_LIB
#define BUTTONS_LIB

#define STEP_BUTTON PA0
#define RED_LEDS_BUTTON PA1
#define YELLOW_LEDS_BUTTON PA2
#define BARRIER_BUTTON PA3
#define CLOSED_BUTTON PA4
#define OPEN_BUTTON PA5
#define MODE_BUTTON PA6
#define EMERGENCY_BUTTON PA7
#define MOTOR_OPEN_BUTTON PC7
#define MOTOR_CLOSE_BUTTON PC6

#define STATUS_EMERGENCY_BUTTON !(PINA & _BV(EMERGENCY_BUTTON))
#define STATUS_STEP_BUTTON !(PINA & _BV(STEP_BUTTON))
#define STATUS_MODE_BUTTON !(PINA & _BV(MODE_BUTTON))
#define STATUS_BARRIER_BUTTON !(PINA & _BV(BARRIER_BUTTON))
#define STATUS_CLOSED_BUTTON !(PINA & _BV(CLOSED_BUTTON))
#define STATUS_OPEN_BUTTON !(PINA & _BV(OPEN_BUTTON))
#define STATUS_RED_LEDS_BUTTON !(PINA & _BV(RED_LEDS_BUTTON))
#define STATUS_YELLOW_LEDS_BUTTON !(PINA & _BV(YELLOW_LEDS_BUTTON))
#define STATUS_MOTOR_OPEN_BUTTON !(PINC & _BV(MOTOR_OPEN_BUTTON))
#define STATUS_MOTOR_CLOSE_BUTTON !(PINC & _BV(MOTOR_CLOSE_BUTTON))

// configure button pins as input
void initButtons(void);

char readEmergencyButton();
char readStepButton();
char readModeButton();
char readBarrierButton();
char readClosedButton();
char readOpenButton();
char readRedLedsButton();
char readYellowLedsButton();

#endif // !BUTTONS_LIB
