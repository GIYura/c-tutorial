#ifndef CAR_H
#define CAR_H

/* forward declaretion */
struct car_t;

/*
@brief: Create car
@in: none
@out: pointer to car_t
*/
struct car_t* CarCreate(void);

/*
@brief: Car init
@in: pointer to car_t
@in: brand
@out: none
*/
void CarInit(struct car_t* car, const char* const brand);

/*
@brief: De init car
@in: pointer to car_t
@out: none
*/
void CarDeinit(struct car_t* car);

/*
@brief: Car start
@in: pointer to car_t
@out: none
*/
void CarStart(struct car_t* car);

/*
@brief: Car stop
@in: pointer to car_t
@out: none
*/
void CarStop(struct car_t* car);

/*
@brief: Get engine temperature
@in: pointer to car_t
@out: temperature value
*/
float CarGetEngineTemperature(struct car_t* car);

#endif /* CAR_H */

