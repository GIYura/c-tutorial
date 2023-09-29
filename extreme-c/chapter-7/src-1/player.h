#ifndef PLAYER_H
#define PLAYER_H

/* forward declaration */
struct player_t;
struct gun_t;

/*
@brief: Create a player
@in: none
@out: struct player_t*
*/
struct player_t* PlayerCreate(void);

/*
@brief: Initialization of the player
@in: struct player_t*
@in: char* - player name
@out: none
*/
void PlayerInit(struct player_t* player, const char* const name);

/*
@brief: Deinitialization of the player
@in: struct player_t*
@out: none
*/
void PlayerDeinit(struct player_t* player);

/*
@brief: Force player to pick up the gun
@out: struct car_t*
@out: struct gun_t*
@out: none
*/
void PlayerPickGun(struct player_t* player, struct gun_t* gun);

/*
@brief: Force player to shoot
@in: struct player_t*
@out: none
*/
void PlayerShoot(struct player_t* player);

/*
@brief: Force player to drpo the gun
@in: struct player_t*
@out: none
*/
void PlayerDropGun(struct player_t* player);

#endif /* PLAYER_H */

