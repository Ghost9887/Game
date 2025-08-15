#include "player.h"
#include "projectile.h"
#include "raylib.h"
#include "weapon.h"
#include "enemy.h"
#include "shotgun.h"
#include <string.h>
#include <math.h>
#include <stdio.h>

Texture2D playerTexture;

Player createPlayerObject() {
  Player player;
  player.x = (float)SCREENWIDTH / (float)2;
  player.y = (float)SCREENHEIGHT / (float)2;
  player.width = 50; //can be adjusted depending on the sprite size
  player.height = 64;
  player.health = 100;
  player.maxHealth = 100;
  player.money = 0;
  player.speed = 150.0f;
  player.canShoot = false;
  player.invTime = 0.0f;
  player.timer;
  player.weapon; // defualt: pistol

  //animations
  player.currentFrame = 0;
  player.frameTime = 0.0f;
  player.frameSpeed = 0.1f; // seconds per frame
  // used for selecting the coordinates on the sprite sheet
  player.frameRec = (Rectangle){ 0.0f, 0.0f, 64.0f, 64.0f};
  return player;
}

void drawPlayer(Player *player) {
  Vector2 pos = {
    player->x,
    player->y
  };
  DrawTextureRec(playerTexture, player->frameRec, pos, WHITE);

  //hitbox debug
  //DrawRectangle(pos.x, pos.y, player->width, player->height, RED);
}

void loadPlayerTextures(){
  // loading from assets
  playerTexture = LoadTexture("assets/player/playertest.png");
}

void updatePlayerAnimation(Player *player) {
    player->frameTime += GetFrameTime();
    if (player->frameTime >= player->frameSpeed) {
        player->frameTime = 0.0f;
        player->currentFrame++;
        if (player->currentFrame > 2) player->currentFrame = 0;
        player->frameRec.y = (float)player->currentFrame * 64.0f;
    }
}

void playerMovement(Player *player) {
  float deltaTime = GetFrameTime();
  if (IsKeyDown(KEY_A) && player->x > 0)
    player->x -= player->speed * deltaTime;
  if (IsKeyDown(KEY_D) && player->x + player->width < SCREENWIDTH)
    player->x += player->speed * deltaTime;
  if (IsKeyDown(KEY_S) && player->y + player->height < SCREENHEIGHT)
    player->y += player->speed * deltaTime;
  if (IsKeyDown(KEY_W) && player->y > 0)
    player->y -= player->speed * deltaTime;
}

void playerShoot(Player *player, Projectile *projectileArr) {
  if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)){
    int indexToReplace;
    for (indexToReplace = 0; indexToReplace < MAXPROJECTILES; indexToReplace++) {
      if (!projectileArr[indexToReplace].active) {
        break;
      }
    }
    player->canShoot = false;
    player->timer = player->weapon->fireRate;

  //check wether we can spawn more projectiles
    if (indexToReplace < MAXPROJECTILES) {
       reduceAmmo(player->weapon);

      //dont like it here havent found a better place for it yet
      if(strcmp(player->weapon->type, "spreadshot") == 0){
        spreadShot(projectileArr, player);
      }else{
        projectileArr[indexToReplace] = createProjectile(player, player->weapon, 0);
      }
      
    }
  }
}

bool checkIfPlayerCanShoot(Player *player) {
  if (player->timer >= 0) {
    player->timer--;
    return false;
  }
  else if(getMagAmmo(player->weapon) <= 0){
    return false;
  }
  else if (player->timer <= 0) {
    player->canShoot = true;
  }
  return true;
}

void playerLoseHealth(Enemy *enemy, Player *player) {
  if (!isPlayerInvulnerable(player)) {
    player->health -= enemy->damage;
    player->invTime += 3.0f;
  }
}

void invTimer(Player *player) {
  if (player->invTime > 0.0f) {
    player->invTime -= GetFrameTime();
  } else {
    player->invTime = 0.0f;
  }
}

bool isPlayerInvulnerable(Player *player) {
  if (player->invTime > 0.0f) {
    return true;
  }
  return false;
}

void addMoney(Player *player, int money){
  player->money += money;
}

void updatePlayer(Player *player) {
  playerMovement(player);
  updatePlayerAnimation(player);
  drawPlayer(player);
  invTimer(player);
}
