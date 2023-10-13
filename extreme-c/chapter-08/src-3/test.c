#include <stdio.h>
#include <stdlib.h>

#include "led.h"

#define LED_PIN 10

int main(int argc, char* argv[])
{
    printf("LED create\n");
    struct led_t* m_led = LedCreate();

    printf("LED init\n");
    LedInit(m_led, LED_PIN, true);

    LedOn(m_led);
    if (LedGetState(m_led) == 1)
        printf("LED ON\n");
    else
        printf("LED OFF\n");

    LedOff(m_led);
    if (LedGetState(m_led) == 0)
        printf("LED OFF\n");
    else
        printf("LED_ON\n");

    printf("LED destroyed\n");
    LedDeinit(m_led);
    free(m_led);

    return 0;
}
