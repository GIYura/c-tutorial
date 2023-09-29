#ifndef GUN_H
#define GUN_H

#include <stdbool.h>

/* forward declaration */
struct gun_t;

/*
@brief: Create gun
@in: none
@out: struct gun_t*
*/
struct gun_t* GunCreate(void);

/*
@brief: Initialize gun
@in: struct gun_t*
@in: number bullets
@out: none
*/
void GunInit(struct gun_t* gun, int bullets);
/*
@brief: Deinit gun
@in: struct gun_t*
@out: none
*/
void GunDeinit(struct gun_t* gun);
/*
@brief: Trigger gun
@in: struct gun_t*
@out: none
*/
void GunTrigger(struct gun_t* gun);
/*
@brief: Refill gun
@in: struct gun_t*
@out: none
*/
void GunRefill(struct gun_t* gun);
/*
@brief: Check whether the gun is full or not
@in: struct gun_t*
@out: true - there are some bullets in the gun; false - otherwise
*/
bool GunHasBullets(struct gun_t* gun);

#endif /* GUN_H */

