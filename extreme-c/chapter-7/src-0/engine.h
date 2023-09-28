#ifndef ENGINE_H
#define ENGINE_H

/* forward declaration */
struct engine_t;

/*
@brief: Create engine (allocate memory)
@in: none
@out: struct engine_t* - pointer to allocated memory
*/
struct engine_t* EngineCreate(void);

/*
@brief: Init engine
@in: struct engine_t* - pointer to engine
@out: none
*/
void EngineInit(struct engine_t* engine);

/*
@brief: Deinit engine
@in: struct engine_t* - pointer to engine
@out: none
*/
void EngineDeinit(struct engine_t* engine);

/*
@brief: Engine turn on
@in: struct engine_t* - pointer to engine
@out: none
*/
void EngineTurnOn(struct engine_t* engine);

/*
@brief: Engine turn off
@in: struct engine_t* - pointer to engine
@out: none
*/
void EngineTurnOff(struct engine_t* engine);

/*
@brief: Get temperature of the engine
@in: struct engine_t* - pointer to engine
@out: none
*/
float EngineGetTemperature(struct engine_t* engine);

#endif /* ENGINE_H */

