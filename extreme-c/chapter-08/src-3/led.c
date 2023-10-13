#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "gpio.h"

typedef struct
{
    struct gpio_t* gpio;
} led_t;

led_t* LedCreate(void)
{
    return (led_t*)malloc(sizeof(led_t));
}

void LedInit(led_t* led, int pin, bool direction)
{
    assert(led);
    assert(pin > 0);

    led->gpio = GpioCreate();
    GpioInit(led->gpio, pin, direction);
}

void LedDeinit(led_t* led)
{
    GpioDeinit(led->gpio);
    free(led->gpio);
}

void LedOn(led_t* led)
{
    GpioSet(led->gpio);
}

void LedOff(led_t* led)
{
    GpioClear(led->gpio);
}

int LedGetState(led_t* led)
{
    return GpioGetState(led->gpio);
}

