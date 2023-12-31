#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BULLETS_MAX 10

typedef struct
{
    int bullets;
} gun_t;

gun_t* GunCreate(void)
{
    return (gun_t*)malloc(sizeof(gun_t));
}

void GunInit(gun_t* const gun, int bullets)
{
    assert(bullets <= BULLETS_MAX);

    gun->bullets = bullets;

    printf("Gun initialized\n");
}

void GunDeinit(gun_t* const gun)
{
/**/
}

void GunTrigger(gun_t* const gun)
{
    gun->bullets--;
    printf("Gun shoot\n");
}

void GunRefill(gun_t* const gun)
{
    gun->bullets = BULLETS_MAX;
    printf("Gun refilled\n");
}

bool GunHasBullets(gun_t* const gun)
{
    return gun->bullets > 0;    
}

