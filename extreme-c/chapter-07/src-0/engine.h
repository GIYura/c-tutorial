#ifndef ENGINE_H
#define ENGINE_H

/* forward declaration */
struct engine_t;

/*
@brief: Create engine (allocate memory)
@in: none
@out: struct engine_t*
*/
struct engine_t* EngineCreate(void);

/*
@brief: Init engine
@in: struct engine_t*
@out: none
*/
void EngineInit(struct engine_t* const engine);

/*
@brief: Deinit engine
@in: struct engine_t*
@out: none
*/
void EngineDeinit(struct engine_t* const engine);

/*
@brief: Engine turn on
@in: struct engine_t*
@out: none
*/
void EngineTurnOn(struct engine_t* const engine);

/*
@brief: Engine turn off
@in: struct engine_t*
@out: none
*/
void EngineTurnOff(struct engine_t* const engine);

/*
@brief: Get temperature of the engine
@in: struct engine_t*
@out: float - temperature value
*/
float EngineGetTemperature(struct engine_t* const engine);

#endif /* ENGINE_H */

