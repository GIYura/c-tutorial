#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "engine.h"

typedef struct
{
    char brand[20];
    struct engine_t* engine;
} car_t;

car_t* CarCreate(void)
{
    return (car_t*)malloc(sizeof(car_t));
}

void CarInit(car_t* car, const char* const brand)
{
    car->engine = EngineCreate();
    EngineInit(car->engine);
    
    strncpy(car->brand, brand, sizeof(car->brand));
    printf("%s initialized\n", brand);
}

void CarDeinit(car_t* car)
{
    EngineDeinit(car->engine);
    free(car->engine);
}

void CarStart(car_t* car)
{
    EngineTurnOn(car->engine);
}

void CarStop(car_t* car)
{
    EngineTurnOff(car->engine);
}

float CarGetEngineTemperature(car_t* car)
{
    return EngineGetTemperature(car->engine);
}

