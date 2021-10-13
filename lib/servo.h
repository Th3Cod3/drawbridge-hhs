/*
 * servo.h - XvR 2020
 */

#ifndef _SERVO_H_
#define _SERVO_H_

// PINS
#define PORT_1 PORTE
#define PIN_1 PE4
#define DDR_1 DDRE

#define PORT_2 PORTE
#define PIN_2 PE5
#define DDR_2 DDRE

void init_servo(void);
void servo1_set_percentage(signed char percentage);
void servo2_set_percentage(signed char percentage);

#endif /* _SERVO_H_ */
