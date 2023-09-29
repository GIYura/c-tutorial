#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gun.h"

typedef struct
{
    char* name;
    struct gun_t* gun;
} player_t;

player_t* PlayerCreate(void)
{
    return (player_t*)malloc(sizeof(player_t));
}

void PlayerInit(player_t* player, const char* const name)
{
    player->name = malloc(sizeof(char) * strlen(name) + 1);
    strcpy(player->name, name);
    player->gun = NULL;
    printf("Player initialized\n");
}

void PlayerDeinit(player_t* player)
{
    free(player->name);
}

void PlayerPickGun(player_t* player, struct gun_t* gun)
{
    player->gun = gun;
    printf("Player picked up the gun\n");
}

void PlayerShoot(player_t* player)
{
    GunTrigger(player->gun);
    printf("Player trigger the gun\n");
}

void PlayerDropGun(player_t* player)
{
    player->gun = NULL;
    printf("Player dropped the gun\n");
}

