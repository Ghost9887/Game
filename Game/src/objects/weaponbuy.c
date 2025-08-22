#include "weaponbuy.h"
#include "weapon.h"
#include "pistol.h"
#include "assaultRifle.h"
#include "rocketLauncher.h"
#include "smg.h"
#include "shotgun.h"
#include "ui.h"
#include <string.h>
#include <stdio.h>

extern unsigned int AMOUNTOFWEAPONS;
extern unsigned int AMOUNTOFWEAPONBUYS;

WeaponBuy createWeaponBuy(){
  WeaponBuy weaponBuy;
  weaponBuy.x = 0;
  weaponBuy.y = 0;
  weaponBuy.weapon;
  weaponBuy.weaponCost = 0;
  weaponBuy.ammoCost = 0;
  return weaponBuy;
}

void drawWeaponBuy(WeaponBuy *weaponBuy, Texture2D *weaponTextureArr) {
  Texture2D texture = weaponTextureArr[weaponBuy->weapon->id];
  Rectangle rect = {0, 0, 32, 32};

  // Center the texture on the weaponBuy box
  Vector2 drawPos = {
    weaponBuy->x + (weaponBuy->weapon->width / 2.0f) - (weaponBuy->weapon->width / 2.0f),
    weaponBuy->y + (weaponBuy->weapon->height / 2.0f) - (weaponBuy->weapon->height / 2.0f)
  };

  DrawTextureRec(texture, rect, drawPos, WHITE);
}


void spawnWeaponBuy(WeaponBuy *weaponBuyArr, Weapon *weapon, int x, int y){
  weaponBuyArr[AMOUNTOFWEAPONBUYS].weapon = weapon;
  weaponBuyArr[AMOUNTOFWEAPONBUYS].weaponCost = weapon->weaponCost;
  weaponBuyArr[AMOUNTOFWEAPONBUYS].ammoCost = weapon->ammoCost;
  weaponBuyArr[AMOUNTOFWEAPONBUYS].x = x;
  weaponBuyArr[AMOUNTOFWEAPONBUYS].y = y;
  AMOUNTOFWEAPONBUYS++;
}

//refactor later
void initWeaponBuyArr(WeaponBuy *weaponBuyArr){
  for(int i = 0; i < MAXWEAPONBUYS; i++){
    weaponBuyArr[i] = createWeaponBuy();
  }
}

int checkForCollisionWeaponBuyPlayer(WeaponBuy *weaponBuyArr, Player *player){
  for(int i = 0; i < AMOUNTOFWEAPONBUYS; i++){
  Rectangle weaponBuyRect = {weaponBuyArr[i].x, weaponBuyArr[i].y, weaponBuyArr[i].weapon->width, weaponBuyArr[i].weapon->height};
  Rectangle playerRect = {player->x, player->y, player->width, player->height};
  if(CheckCollisionRecs(weaponBuyRect, playerRect)){
      return i;
    }
  }
  return -1;
}

bool isWeaponOwned(int weaponId, int *weaponHolster) {
  for (int i = 0; i < MAXWEAPONS; i++) {
    if (weaponHolster[i] == weaponId) return true;
  }
  return false;
}

//HUGE FUNCTION MAYBE REFACTOR?
void buyWeapon(WeaponBuy *weaponBuyArr, Player *player, Weapon *weaponArr, int *weaponHolster){
  int index = checkForCollisionWeaponBuyPlayer(weaponBuyArr, player);
  if (index != -1) {
    Weapon *newWeapon = &weaponArr[index];
    //check if we already have the weapon in our holster
    bool alreadyOwned = isWeaponOwned(newWeapon->id, weaponHolster);
    Color textColour;

    if (alreadyOwned) {
      //determine what colour the text should be if the player has enough money
      textColour = (player->money >= newWeapon->ammoCost) ? GREEN : RED;
      drawAmmoBuyText(textColour, &weaponBuyArr[index]);
      if (IsKeyPressed(KEY_E) && player->money >= newWeapon->ammoCost && newWeapon->currentReserveSize < newWeapon->maxReserveSize) {
        player->money -= newWeapon->ammoCost;
        replenishAmmo(player, newWeapon);
      }
      return;
    } else {
      textColour = (player->money >= newWeapon->weaponCost) ? GREEN : RED;
      drawWeaponBuyText(textColour, &weaponBuyArr[index]);
    }
    if (IsKeyPressed(KEY_E) && player->money >= newWeapon->weaponCost) {
      int currentWeaponId = player->weapon->id;
      int slotToReplace = -1;
      bool foundEmptySlot = false;
      for (int i = 0; i < MAXWEAPONS; i++) {
        if (weaponHolster[i] == -1) {
          slotToReplace = i;
          foundEmptySlot = true;
          break;
        }
      }
      if (!foundEmptySlot) {
        for (int i = 0; i < MAXWEAPONS; i++) {
          if (weaponHolster[i] == currentWeaponId) {
            slotToReplace = i;
            break;
          }
        }
      }
      if (slotToReplace != -1) {
        weaponHolster[slotToReplace] = newWeapon->id;
        player->money -= newWeapon->weaponCost;
        replaceWeapon(newWeapon, player);
      }
    }
  }
}

void updateWeaponBuy(WeaponBuy *weaponBuyArr, Player *player, Weapon *weaponArr, int *weaponHolster, Texture2D *weaponTextureArr) {
  for (int i = 0; i < AMOUNTOFWEAPONBUYS; i++) {
    drawWeaponBuy(&weaponBuyArr[i], weaponTextureArr);
  }

  buyWeapon(weaponBuyArr, player, weaponArr, weaponHolster);
}


