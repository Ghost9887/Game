#ifndef PLAYER_H
#define PLAYER_H

#include "common.h"
#include "raylib.h"
#include <stdbool.h>

Player createPlayerObject(Weapon weapon);
void drawPlayer(Player *player);
void playerMovement(Player *player);
bool checkIfPlayerCanShoot(Player *player);
void playerShoot(Player *player, Projectile *projectileArr, int indexOfEnemy,
                 Coins *coins);
void playerLoseHealth(Enemy *enemy, Player *player);
bool isPlayerInvulnerable(Player *player);
void invTimer(Player *player);
void updatePlayer(Player *player, Weapon *weapon);

#endif
