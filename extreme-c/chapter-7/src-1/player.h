#ifndef PLAYER_H
#define PLAYER_H

struct player_t;
struct gun_t;

struct player_t* PlayerCreate(void);
void PlayerInit(struct player_t* player, const char* const name);
void PlayerDeinit(struct player_t* player);
void PlayerPickGun(struct player_t* player, struct gun_t* gun);
void PlayerShoot(struct player_t* player);
void PlayerDropGun(struct player_t* player);

#endif /* PLAYER_H */
