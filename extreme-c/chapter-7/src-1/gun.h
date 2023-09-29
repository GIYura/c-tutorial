#ifndef GUN_H
#define GUN_H

#include <stdbool.h>

struct gun_t;

struct gun_t* GunCreate(void);
void GunInit(struct gun_t* gun, int bullets);
void GunDeinit(struct gun_t* gun);
void GunTrigger(struct gun_t* gun);
void GunRefill(struct gun_t* gun);
bool GunHasBullets(struct gun_t* gun);

#endif /* GUN_H */
