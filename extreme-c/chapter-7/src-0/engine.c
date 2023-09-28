#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_ENGINE_TEMPERATURE  11.15

typedef enum
{
    ON,
    OFF
} state_t;

typedef struct
{
    state_t state;
    float temperature;
} engine_t;

engine_t* EngineCreate(void)
{
    return (engine_t*)malloc(sizeof(engine_t));
}

void EngineInit(engine_t* engine)
{
    engine->state = OFF;
    engine->temperature = DEFAULT_ENGINE_TEMPERATURE;
}

void EngineDeinit(engine_t* engine)
{
    /* nothing to do */
}

void EngineTurnOn(engine_t* engine)
{
    if (engine->state == ON)
        return;

    engine->state = ON;
    engine->temperature = 90.555;
}

void EngineTurnOff(engine_t* engine)
{
    if (engine->state == OFF)
        return;

    engine->state = OFF;
    engine->temperature = DEFAULT_ENGINE_TEMPERATURE;
}

float EngineGetTemperature(engine_t* engine)
{
    return engine->temperature;
}

