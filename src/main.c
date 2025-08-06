#include "coins.h"
#include "enemy.h"
#include "player.h"
#include "projectile.h"
#include "raylib.h"
#include "roundSystem.h"
#include "ui.h"
#include "weapon.h"
#include <stdbool.h>

// GLOBAL VARIABLES
unsigned int ENEMYCOUNTER = 0;
unsigned int CURRENTSPAWNEDENEMIES = 0;

void updateGameState(Player *player, Enemy *enemyArr, Projectile *projectileArr,
                     Round *rnd, Coins *coins, Weapon *weaponArr);

int main(void) {

  InitWindow(SCREENWIDTH, SCREENHEIGHT, "raylib game");

  SetTargetFPS(TARGETFPS);

  // creating all objects for the game
  Projectile projectileArr[MAXPROJECTILES];
  initProjectileArray(projectileArr);

  Enemy enemyArr[MAXENEMIES];
  initEnemyArr(enemyArr);

  Round rnd = createRoundObject();
  Coins coins = createCoins();

  // houses all the weapons
  Weapon weaponArr[10];
  initWeaponArr(weaponArr);

  Player player = createPlayerObject();
  player.weapon = weaponArr[0]; // the first weapon(pistol)

  // start the first round
  startRound(&rnd, enemyArr);
  // MAIN GAME LOOP

  while (!WindowShouldClose()) {

    BeginDrawing();

    ClearBackground(RAYWHITE);
    // UPDATE ALL OF THE GAME STATES
    updateGameState(&player, enemyArr, projectileArr, &rnd, &coins, weaponArr);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}

void updateGameState(Player *player, Enemy *enemyArr, Projectile *projectileArr,
                     Round *rnd, Coins *coins, Weapon *weaponArr) {

  updatePlayer(player, weaponArr);

  // checks if the round should end
  updateBreak(rnd, enemyArr);

  updateWeapon(weaponArr, player);

  // drawing
  drawUI(player->health, ENEMYCOUNTER, player->invTime, rnd->round,
         getCoins(coins), CURRENTSPAWNEDENEMIES);

  // only do these if there are enemies or the round hasn't ended yet
  if (!inBreak(rnd)) {
    // only call this if there are more enemies that need to be spawned druring
    // the round
    if (MAXSPAWNENEMIES <= ENEMYCOUNTER) { 
      createEnemies(enemyArr, getAmountOfEnemies(rnd));
    }
    // check if the player has anything to shoot at if so create the projectile
    // with the target of the indexOfEnemy
    int indexOfEnemy = findClosestEnemyToPlayer(enemyArr, player, coins);
    // check if the closes enemy is in range of shooting
    if (indexOfEnemy != -2 && checkIfPlayerCanShoot(player)) {
      playerShoot(player, projectileArr, indexOfEnemy, coins);
    }
    updateProjectiles(projectileArr, enemyArr, coins);
  }
  updateEnemy(enemyArr, player);
}
