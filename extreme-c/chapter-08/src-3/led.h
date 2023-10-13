#ifndef LED_H
#define LED_H

#include <stdbool.h>

/* forward declaration */
struct led_t;

/*
@brief: Create led (allocate memory)
@in: none
@out: struct led_t*
*/
struct led_t* LedCreate(void);

/*
@brief: Init led
@in: struct led_t*
@in: int pin - led pin number
@in: bool direction - true out; false - otherwise
@out: none
*/
void LedInit(struct led_t* led, int pin, bool direction);

/*
@brief: Deinit led
@in: struct led_t*
@out: none
*/
void LedDeinit(struct led_t* led);

/*
@brief: Led on
@in: struct led_t*
@out: none
*/
void LedOn(struct led_t* led);

/*
@brief: Led off
@in: struct led_t*
@out: none
*/
void LedOff(struct led_t* led);

/*
@brief: Get led state
@in: struct led_t*
@out: int - 1 - led on; 0 - led off
*/
int LedGetState(struct led_t* led);

#endif /* LED_H */

