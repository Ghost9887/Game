#include "enemy.h"
#include "player.h"
#include "projectile.h"
#include "raylib.h"
#include "roundSystem.h"
#include "ui.h"
#include "weapon.h"
#include "pickup.h"
#include "weaponbuy.h"
#include "common.h"
#include "perk.h"
#include <stdbool.h>
#include <stdio.h>

// GLOBAL VARIABLES
unsigned int ENEMYCOUNTER = 0;
unsigned int CURRENTSPAWNEDENEMIES = 0;
unsigned int BIGENEMYCOUNTER = 0;
unsigned int AMOUNTOFWEAPONS = 6;
int GAMETIME = 0;


void updateGameState(Player *player, Enemy *enemyArr, Projectile *projectileArr,
                     Round *rnd, Weapon *weaponArr, Pickup *pickupArr, WeaponBuy *weaponBuyArr,
                     int *weaponHolster, Perk *perkArr, Texture2D *weaponTextureArr,
                     Texture2D *enemyTexturesArr);

int main(void) {

  InitWindow(SCREENWIDTH, SCREENHEIGHT, "raylib game");

  /*
  //hide the cursor
  HideCursor();
  */

  SetTargetFPS(TARGETFPS);

  // creating all objects for the game
  Projectile projectileArr[MAXPROJECTILES];
  initProjectileArray(projectileArr);

  Enemy enemyArr[MAXSPAWNENEMIES];
  initEnemyArr(enemyArr);

  Round rnd = createRoundObject();

  // houses all the weapons
  Weapon weaponArr[AMOUNTOFWEAPONS];
  initWeaponArr(weaponArr);

  //players weapons in inventory
  int weaponHolster[MAXWEAPONS];
  initWeaponHolster(weaponHolster, weaponArr);

  //define a num of weaponbuys later
  WeaponBuy weaponBuyArr[AMOUNTOFWEAPONS];
  initWeaponBuyArr(weaponBuyArr, weaponArr);

  //houses all pickups
  Pickup pickupArr[MAXPICKUPS];
  initPickupArray(pickupArr);

  //define a amount of perk machines later
  Perk perkArr[2];
  initPerkArr(perkArr);

  loadPlayerTextures();

  Texture2D weaponTextureArr[AMOUNTOFWEAPONS]; 
  loadWeaponTextures(weaponTextureArr);

  Texture2D enemyTexturesArr[MAXSPAWNENEMIES];
  loadEnemyTextures(enemyTexturesArr);

  Player player = createPlayerObject();
  player.weapon = &weaponArr[0]; 


  // start the first round
  startRound(&rnd, enemyArr);


  // MAIN GAME LOOP
  
  while (!WindowShouldClose()) {
      BeginDrawing();

      ClearBackground(RAYWHITE);
      // UPDATE ALL OF THE GAME STATES
        updateGameState(&player, enemyArr, projectileArr, &rnd, weaponArr, 
                    pickupArr, weaponBuyArr, weaponHolster, perkArr, weaponTextureArr,
                    enemyTexturesArr);
      EndDrawing();
  }

  CloseWindow();

  return 0;
}

void updateGameState(Player *player, Enemy *enemyArr, Projectile *projectileArr,
                     Round *rnd, Weapon *weaponArr, Pickup *pickupArr, WeaponBuy *weaponBuyArr,
                     int *weaponHolster, Perk *perkArr, Texture2D *weaponTextureArr, 
                     Texture2D *enemyTexturesArr) {

  updatePlayer(player, enemyArr);

  // checks if the round should end
  updateRound(rnd, enemyArr);

  updateWeapon(weaponArr, player, weaponHolster, weaponTextureArr);

  updatePickups(pickupArr, player);

  updatePerk(perkArr, player);

  updateWeaponBuy(weaponBuyArr, player, weaponArr, weaponHolster, weaponTextureArr);

  drawUI(player->health, ENEMYCOUNTER, player->invTime, rnd->round,player->money,
         CURRENTSPAWNEDENEMIES, GetFPS(),
         player->weapon->currentMagSize, player->weapon->currentReserveSize, player->weapon->reloadTimer);
  
  if (checkIfPlayerCanShoot(player) && !isReloading(player->weapon)) {
    playerShoot(player, projectileArr);
  }
  updateProjectiles(projectileArr, enemyArr, player);


  // only do these if there are enemies or the round hasn't ended yet
  if (!inBreak(rnd)) {
    // only call this if there are more enemies that need to be spawned druring
    int remainingToSpawn = ENEMYCOUNTER - CURRENTSPAWNEDENEMIES;
    if (remainingToSpawn > 0) {
      createEnemies(enemyArr, remainingToSpawn, getRound(rnd));
    }

    //this fixes a bug when multiple enemies are destroyed and the ENEMYCOUNTER 
    //drops below MAXSPAWNENEMIES we still want to create more
   
   }else{
    //reset the big enemy counter once the round is over
    resetBigEnemyCounter();
  }

  updateEnemy(enemyArr, player, pickupArr, enemyTexturesArr);
}
