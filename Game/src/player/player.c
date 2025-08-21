#include "player.h"
#include "projectile.h"
#include "raylib.h"
#include "weapon.h"
#include "enemy.h"
#include "shotgun.h"
#include <string.h>
#include <math.h>
#include <stdio.h>

extern unsigned int CURRENTSPAWNEDENEMIES;

Texture2D playerTexture;

Player createPlayerObject() {
  Player player;
  player.x = (float)SCREENWIDTH / (float)2;
  player.y = (float)SCREENHEIGHT / (float)2;
  player.width = 64; //can be adjusted depending on the sprite size
  player.height = 64;
  player.rotation = 0.0f;
  player.health = 100;
  player.maxHealth = 100;
  player.money = 0;
  player.speed = 180.0f;
  player.maxSpeed = 180.0f; 
  player.canShoot = false;
  player.invTime = 0.0f;
  player.timer;
  player.weapon; // defualt: pistol

  //animations
  player.currentFrame = 0;
  player.frameTime = 0.0f;
  player.frameSpeed = 0.3f; // seconds per frame
  // used for selecting the coordinates on the sprite sheet
  player.frameRec = (Rectangle){ 0.0f, 0.0f, 64.0f, 64.0f};
  player.ads = false;
  return player;
}

void drawPlayer(Player *player, Camera2D *camera) {
    float rotation = getRotationOfPlayer(player, camera);
    Rectangle source = player->frameRec; 
    Rectangle dest = {
        player->x + player->width / 2,
        player->y + player->height / 2,
        player->frameRec.width,
        player->frameRec.height,
    };
    Vector2 pivot = { player->frameRec.width / 2.0f, player->frameRec.height / 2.0f };
    player->rotation = rotation;
    DrawTexturePro(playerTexture, source, dest, pivot, rotation, WHITE);
}


float getRotationOfPlayer(Player *player, Camera2D *camera){
  Vector2 mousePosition = GetScreenToWorld2D(GetMousePosition(), *camera);
 float rad = atan2(mousePosition.y - player->y, mousePosition.x - player->x);
  float degree = rad * (180.0f / 3.14);
  return degree;
}

void loadPlayerTextures(){
  // loading from assets
  playerTexture = LoadTexture("assets/player/player.png");
}

void updatePlayerAnimation(Player *player) {
    player->frameTime += GetFrameTime();
    if (player->frameTime >= player->frameSpeed) {
        player->frameTime = 0.0f;
        player->currentFrame++;
        if (player->currentFrame > 2) player->currentFrame = 0;
        player->frameRec.y = (float)player->currentFrame * player->frameRec.width;
    }
}

void playerMovement(Player *player) {
  float deltaTime = GetFrameTime();
  if (IsKeyDown(KEY_A))
    player->x -= player->speed * deltaTime;
  if (IsKeyDown(KEY_D))
    player->x += player->speed * deltaTime;
  if (IsKeyDown(KEY_S))
    player->y += player->speed * deltaTime;
  if (IsKeyDown(KEY_W))
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
        if(!player->ads){
          projectileArr[indexToReplace] = createProjectile(player, player->weapon, (float)GetRandomValue(-player->weapon->spread, player->weapon->spread));
        }
        else{
          //if ads have max accuracy
          projectileArr[indexToReplace] = createProjectile(player, player->weapon, 0);
        }
      }
      
    }
  }
}

void ADS(Player *player, Enemy *enemyArr) {
    if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
        if (!player->ads) {
            player->speed -= 80;
            player->ads = true;
        }
        float rotation = player->rotation;
        float muzzleOffset = player->width * 0.4f; 
        Vector2 origin = {
            player->x + player->width / 2 + cosf(rotation * DEG2RAD ) * muzzleOffset,
            player->y + player->height / 2 + sinf(rotation * DEG2RAD) * muzzleOffset
        };
        float range = player->weapon->range;
        Vector2 direction = {
            cosf(rotation * DEG2RAD),
            sinf(rotation * DEG2RAD)
        };
        Vector2 hitPoint = {
            origin.x + direction.x * range,
            origin.y + direction.y * range
        };
        for (float t = 0; t < range; t++) {
            Vector2 point = {
                origin.x + direction.x * t,
                origin.y + direction.y * t
            };
            for (int i = 0; i < CURRENTSPAWNEDENEMIES; i++) {
              if (enemyArr[i].active) {
                  Enemy enemy = enemyArr[i];
                  Rectangle enemyHitbox = {
                      enemy.x,
                      enemy.y,
                      enemy.width,
                      enemy.height
                  };
                  if (CheckCollisionPointRec(point, enemyHitbox)) {
                      hitPoint = point;
                      t = range;
                      break;
                  }
              }
            }
        }
        DrawLineEx(origin, hitPoint, 1.0f, RED);
    } else {
        if (player->ads) {
            player->speed += 80;
            player->ads = false;
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

void updatePlayer(Player *player, Enemy *enemyArr, Camera2D *camera) {
  playerMovement(player);
  ADS(player, enemyArr);
  updatePlayerAnimation(player);
  drawPlayer(player, camera);
  invTimer(player);
}
