#include "enemy.h"
#include "player.h"
#include "projectile.h"
#include "raylib.h"
#include "roundSystem.h"
#include "ui.h"
#include "weapon.h"
#include "pickup.h"
#include <stdbool.h>

// GLOBAL VARIABLES
unsigned int ENEMYCOUNTER = 0;
unsigned int CURRENTSPAWNEDENEMIES = 0;
unsigned int BIGENEMYCOUNTER = 0;

void updateGameState(Player *player, Enemy *enemyArr, Projectile *projectileArr,
                     Round *rnd, Weapon *weaponArr, Pickup *pickupArr);

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

  Enemy enemyArr[MAXENEMIES];
  initEnemyArr(enemyArr);

  Round rnd = createRoundObject();

  // houses all the weapons
  Weapon weaponArr[10];
  initWeaponArr(weaponArr);

  //houses all pickups
  Pickup pickupArr[MAXPICKUPS];
  initPickupArray(pickupArr);

  Player player = createPlayerObject();
  player.weapon = &weaponArr[0]; // the first weapon(pistol)

  // start the first round
  startRound(&rnd, enemyArr);
  // MAIN GAME LOOP
  
  while (!WindowShouldClose()) {

    BeginDrawing();

     ClearBackground(RAYWHITE);
    // UPDATE ALL OF THE GAME STATES
    updateGameState(&player, enemyArr, projectileArr, &rnd, weaponArr, pickupArr);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}

void updateGameState(Player *player, Enemy *enemyArr, Projectile *projectileArr,
                     Round *rnd, Weapon *weaponArr, Pickup *pickupArr) {

  updatePlayer(player);

  // checks if the round should end
  updateRound(rnd, enemyArr);

  updateWeapon(weaponArr, player);

  updatePickups(pickupArr, player);

  drawUI(player->health, ENEMYCOUNTER, player->invTime, rnd->round,player->money,
         CURRENTSPAWNEDENEMIES, GetFPS(),
         player->weapon->currentMagSize, player->weapon->currentReserveSize, player->weapon->reloadTimer);
  
  if (checkIfPlayerCanShoot(player) && !isReloading(player->weapon)) {
    playerShoot(player, projectileArr);
  }
  updateProjectiles(projectileArr, enemyArr, player);


  // only do these if there are enemies or the round hasn't ended yet
  if (!inBreak(rnd)) {
    resetBigEnemyCounter();
    // only call this if there are more enemies that need to be spawned druring
    int remainingToSpawn = ENEMYCOUNTER - CURRENTSPAWNEDENEMIES;
    if (remainingToSpawn > 0) {
      createEnemies(enemyArr, remainingToSpawn, getRound(rnd));
    }

    //this fixes a bug when multiple enemies are destroyed and the ENEMYCOUNTER 
    //drops below MAXSPAWNENEMIES we still want to create more
   
   }

  updateEnemy(enemyArr, player, pickupArr);
}
