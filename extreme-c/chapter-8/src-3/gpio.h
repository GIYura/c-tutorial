#ifndef GPIO_H
#define GPIO_H

#include <stdbool.h>

/* forward declaration */
struct gpio_t;

/*
@brief: Create gpio (allocate memory)
@in: none
@out: struct gpio_t*
*/
struct gpio_t* GpioCreate(void);

/*
@brief: Init gpio
@in: struct gpio_t*
@in: int number - gpio pin number
@in: bool direction - true - output, false - otherwise
@out: none
*/
void GpioInit(struct gpio_t* gpio, int number, bool direction);

/*
@brief: Deinit gpio
@in: struct gpio_t*
@out: none
*/
void GpioDeinit(struct gpio_t* gpio);

/*
@brief: Set gpio pin
@in: struct gpio_t*
@out: none
*/
void GpioSet(struct gpio_t* gpio);

/*
@brief: Clear gpio pin
@in: struct gpio_t*
@out: none
*/
void GpioClear(struct gpio_t* gpio);

/*
@brief: Get gpio pin state
@in: struct gpio_t*
@out: int - 1 gpio pin - high; 0 - gpio pin - low
*/
int GpioGetState(struct gpio_t* gpio);

#endif /* GPIO_H */

