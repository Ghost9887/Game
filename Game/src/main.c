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
#include "map.h"
#include "camera.h"
#include "chunk.h"
#include "perkBuy.h"
#include "perk.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "raymath.h"

// GLOBAL VARIABLES
unsigned int ENEMYCOUNTER = 0;
unsigned int CURRENTSPAWNEDENEMIES = 0;
unsigned int BIGENEMYCOUNTER = 0;
unsigned int AMOUNTOFWEAPONS = 6;
unsigned int AMOUNTOFWEAPONBUYS = 0;
unsigned int AMOUNTOFPERKMACHINES = 0;
unsigned int AMOUNTOFSOLIDBLOCKS = 0;

void updateGameState(Player *player, Enemy *enemyArr, Projectile *projectileArr,
                     Round *rnd, Weapon *weaponArr, Pickup *pickupArr, WeaponBuy *weaponBuyArr,
                     int *weaponHolster, Texture2D *weaponTextureArr,
                     Texture2D *enemyTexturesArr, Camera2D *camera, PerkBuy *perkBuyArr, Texture2D *perkTexturesArr,
                     Tile *solidTilesArr);

int main(void) {

  InitWindow(SCREENWIDTH, SCREENHEIGHT, "raylib game");

  /*
  //hide the cursor
  HideCursor();
  */

  SetTargetFPS(TARGETFPS);

  //load the map
  Tile tileArr[MAXTILES];
  Texture2D tileTextureArr[MAXTILES];
  int mapArr[MAXTILES];
  loadTileTextures(tileTextureArr);
  initTileArr(tileArr);
  loadMap(tileArr);
  drawGrid(tileArr, 32);

  Camera2D camera;
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
  WeaponBuy weaponBuyArr[MAXWEAPONBUYS];
  initWeaponBuyArr(weaponBuyArr);

  //houses all pickups
  Pickup pickupArr[MAXPICKUPS];
  initPickupArray(pickupArr);

  //define a amount of perk machines later
  Perk perkArr[2]; 
  initPerkArr(perkArr);
 
  PerkBuy perkBuyArr[MAXPERKMACHINES];
  initPerkBuyArr(perkBuyArr);

  loadPlayerTextures();

  Texture2D weaponTextureArr[AMOUNTOFWEAPONS]; 
  loadWeaponTextures(weaponTextureArr);

  Texture2D enemyTexturesArr[MAXSPAWNENEMIES];
  loadEnemyTextures(enemyTexturesArr);

  Texture2D perkTexturesArr[MAXPERKMACHINES];
  loadPerkBuyTextures(perkTexturesArr);

  Player player = createPlayerObject();
  player.weapon = &weaponArr[0]; 

  initCamera(&camera, &player);

  //chunks
  Chunk chunkArr[9];
  initChunkArr(chunkArr);

  // start the first round
  startRound(&rnd, enemyArr);

  
  Tile solidTilesArr[AMOUNTOFSOLIDBLOCKS];

  spawnObjects(weaponBuyArr, weaponArr, perkBuyArr, perkArr, tileArr, solidTilesArr);
  // MAIN GAME LOOP
  
  while (!WindowShouldClose()) {
      BeginDrawing();
      ClearBackground(BLACK);
      BeginMode2D(camera);
      
      float wheel = GetMouseWheelMove();
    if (wheel != 0){
      // Get the world point that is under the mouse
      Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);
      // Set the offset to where the mouse is
      camera.offset = GetMousePosition();
      // Set the target to match, so that the camera maps the world space point
      // under the cursor to the screen space point under the cursor at any zoom
      camera.target = mouseWorldPos;
      // Zoom increment
      // Uses log scaling to provide consistent zoom speed
      float scale = 0.2f*wheel;
      camera.zoom = Clamp(expf(logf(camera.zoom)+scale), 0.125f, 64.0f);
    }
    //dragging
    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && IsKeyDown(KEY_LEFT_SHIFT)){
       Vector2 delta = GetMouseDelta();
      delta = Vector2Scale(delta, -1.0f/camera.zoom);
      camera.target = Vector2Add(camera.target, delta);
    }

      updateCamera(&camera, &player);
      drawMap(tileArr, tileTextureArr, chunkArr, &camera);
      // UPDATE ALL OF THE GAME STATES
        updateGameState(&player, enemyArr, projectileArr, &rnd, weaponArr, 
                    pickupArr, weaponBuyArr, weaponHolster, weaponTextureArr,
                    enemyTexturesArr, &camera, perkBuyArr, perkTexturesArr, solidTilesArr);
      EndMode2D();

        drawUI(player.health, ENEMYCOUNTER, player.invTime, rnd.round, player.money,
        CURRENTSPAWNEDENEMIES, GetFPS(),
        player.weapon->currentMagSize, player.weapon->currentReserveSize, player.weapon->reloadTimer);
      EndDrawing();
  }

  CloseWindow();

  return 0;
}

void updateGameState(Player *player, Enemy *enemyArr, Projectile *projectileArr,
                     Round *rnd, Weapon *weaponArr, Pickup *pickupArr, WeaponBuy *weaponBuyArr,
                     int *weaponHolster, Texture2D *weaponTextureArr, 
                     Texture2D *enemyTexturesArr, Camera2D *camera, PerkBuy *perkBuyArr, Texture2D *perkTexturesArr,
                     Tile *solidTilesArr) {
  
  updatePlayer(player, enemyArr, camera, solidTilesArr);

  // checks if the round should end
  updateRound(rnd, enemyArr);

  updateWeapon(weaponArr, player, weaponHolster, weaponTextureArr);

  updatePickups(pickupArr, player);
  

  updatePerkBuy(perkBuyArr, player, perkTexturesArr);


  updateWeaponBuy(weaponBuyArr, player, weaponArr, weaponHolster, weaponTextureArr);
 
  if (checkIfPlayerCanShoot(player) && !isReloading(player->weapon)) {
    playerShoot(player, projectileArr);
  }
  updateProjectiles(projectileArr, enemyArr, player);

  
  if(false){
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

  updateEnemy(enemyArr, player, pickupArr, enemyTexturesArr, solidTilesArr);
  }
}
