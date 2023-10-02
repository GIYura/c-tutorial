#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    int pin;
    int state;
    bool direction;
} gpio_t;

gpio_t* GpioCreate(void)
{
    return (gpio_t*)malloc(sizeof(gpio_t));
}

void GpioInit(gpio_t* gpio, int number, bool direction)
{
    assert(gpio);
    assert(number > 0);

    gpio->pin = number;
    gpio->direction = direction;
}

void GpioDeinit(gpio_t* gpio)
{
    /* nothing */
}

void GpioSet(gpio_t* gpio)
{
    gpio->state = 1;
}

void GpioClear(gpio_t* gpio)
{
    gpio->state = 0;
}

int GpioGetState(gpio_t* gpio)
{
    return gpio->state;
}

