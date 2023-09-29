#ifndef CAR_H
#define CAR_H

/* forward declaration */
struct car_t;

/*
@brief: Create car
@in: none
@out: struct car_t*
*/
struct car_t* CarCreate(void);

/*
@brief: Car init
@in: struct car_t*
@in: char* - car brand
@out: none
*/
void CarInit(struct car_t* const car, const char* const brand);

/*
@brief: De init car
@in: struct car_t*
@out: none
*/
void CarDeinit(struct car_t* const car);

/*
@brief: Car start
@in: struct car_t*
@out: none
*/
void CarStart(struct car_t* const car);

/*
@brief: Car stop
@in: struct car_t*
@out: none
*/
void CarStop(struct car_t* const car);

/*
@brief: Get engine temperature
@in: struct car_t*
@out: float - temperature value
*/
float CarGetEngineTemperature(struct car_t* const car);

#endif /* CAR_H */

