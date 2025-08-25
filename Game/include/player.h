#ifndef PLAYER_H
#define PLAYER_H

#include "common.h"
#include "raylib.h"
#include <stdbool.h>

Player createPlayerObject();
void drawPlayer(Player *player, Camera2D *camera);
void playerMovement(Player *player, Tile *solidTileArr);
bool checkIfPlayerCanShoot(Player *player);
void playerShoot(Player *player, Projectile *projectileArr);
void playerLoseHealth(Enemy *enemy, Player *player);
bool isPlayerInvulnerable(Player *player);
void invTimer(Player *player);
void addMoney(Player *player, int money);
void updatePlayer(Player *player, Enemy *enemyArr, Camera2D *camera, Tile *solidTileArr);
void updatePlayerAnimation(Player *player);
void loadPlayerTextures();
void ADS(Player *player, Enemy *enemyArr);
float getRotationOfPlayer(Player *player, Camera2D *camera);

#endif

