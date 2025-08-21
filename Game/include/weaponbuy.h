#ifndef WEAPONBUY_H
#define WEAPONBUY_H

#include "raylib.h"
#include "common.h"
#include <stdbool.h>

WeaponBuy createWeaponBuy();
void drawWeaponBuy(WeaponBuy *weaponBuy, Texture2D *weaponTextureArr);
void spawnWeaponBuy(WeaponBuy *weaponBuy, Weapon *weapon, int x, int y);
void initWeaponBuyArr(WeaponBuy *weaponBuyArr, Weapon *weaponArr);
void updateWeaponBuy(WeaponBuy *weaponBuyArr, Player *player, Weapon *weaponArr, int *weaponHolster, Texture2D *weaponTextureArr);
void buyWeapon(WeaponBuy *weaponBuyArr, Player *player, Weapon *weaponArr, int *weaponHolster);
int checkForCollisionWeaponBuyPlayer(WeaponBuy *weaponBuyArr, Player *player);
bool isWeaponOwned(int weaponId, int *weaponHolster);

#endif
