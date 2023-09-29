#include <stdio.h>
#include <stdlib.h>

#include "player.h"
#include "gun.h"

int main(int argc, char* argv[])
{
    struct gun_t* m_gun = GunCreate();
    GunInit(m_gun, 10);

    struct player_t* m_player = PlayerCreate();
    PlayerInit(m_player, "John");

    PlayerPickGun(m_player, m_gun);

    while (GunHasBullets(m_gun))
    {
        PlayerShoot(m_player);
    }

    PlayerDropGun(m_player);

    PlayerDeinit(m_player);
    free(m_player);

    GunDeinit(m_gun);
    free(m_gun);

    return 0;
}
