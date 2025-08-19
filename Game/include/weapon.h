#ifndef WEAPON_H
#define WEAPON_H

#include "common.h"
#include "raylib.h"

void drawWeapon(Player *player, Texture2D *weaponTextureArr);
void initWeaponArr(Weapon *weaponArr);
void initWeaponHolster(int *weaponHolster, Weapon *weaponArr);
void switchWeapons(Player *player, int *weaponHolster, Weapon *weaponArr);
void replaceWeapon(Weapon *weapon, Player *player);
void updateWeapon(Weapon *weaponArr, Player *player, int *weaponHolster, Texture2D *weaponTextureArr);
void checkReload(Weapon *weapon, Player *player);
int getMagAmmo(Weapon *weapon);
int getReserveAmmo(Weapon *weapon);
void reduceAmmo(Weapon *weapon);
bool isReloading(Weapon *weapon);
float getRotationOfWeapon(Player *player);
void replenishAmmo(Player *player, Weapon *weapon);
void loadWeaponTextures(Texture2D *weaponTextureArr);
void updateWeaponAnimation(Weapon *weapon);

#endif
