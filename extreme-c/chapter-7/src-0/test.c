#include <stdio.h>
#include <stdlib.h>
#include "car.h"

int main(int argc, char* argv[])
{
    struct car_t* m_car = CarCreate();

    CarInit(m_car, "Mercedes");

    printf("Engine Temperature before start: %.2f C\n", CarGetEngineTemperature(m_car));

    CarStart(m_car);

    printf("Engine Temperature after start: %.2f C\n", CarGetEngineTemperature(m_car));

    CarStop(m_car);

    printf("Engine Temperature after stop: %.2f C\n", CarGetEngineTemperature(m_car));

    CarDeinit(m_car);

    free(m_car);
    
    return 0;
}
