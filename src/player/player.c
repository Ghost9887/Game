#include "player.h"
#include "projectile.h"
#include "raylib.h"
#include "weapon.h"
#include "enemy.h"
#include <string.h>
#include <math.h>

Player createPlayerObject() {
  Player player;
  player.x = (float)SCREENWIDTH / (float)2;
  player.y = (float)SCREENHEIGHT / (float)2;
  player.width = 30;
  player.height = 50;
  player.health = 100;
  player.money = 0;
  player.speed = 150.0f;
  player.canShoot = false;
  player.invTime = 0.0f;
  player.timer;
  player.weapon; // defualt: pistol
  return player;
}

void drawPlayer(Player *player) {
  DrawRectangle(player->x, player->y, player->width, player->height, BLUE);
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

void playerShoot(Player *player, Projectile *projectileArr, int indexOfEnemy) {
  int indexToReplace;
  for (indexToReplace = 0; indexToReplace < MAXPROJECTILES; indexToReplace++) {
    if (!projectileArr[indexToReplace].active) {
      break;
    }
  }

  player->canShoot = false;
  Weapon weapon = player->weapon;
  player->timer = weapon.fireRate;

  //check wether we can spawn more projectiles
  if (indexToReplace < MAXPROJECTILES) {

    projectileArr[indexToReplace] = createProjectile(indexOfEnemy, player, &weapon);

    // check if the weapon has type of explosive!
    if (strcmp(player->weapon.type, "explosive") == 0) {
      projectileArr[indexToReplace].explosive = true;
    } else {
      projectileArr[indexToReplace].explosive = false;
    }
  }
}

int findClosestEnemyToPlayer(Enemy *enemyArr, Player *player) {
  int indexOfEnemy;
  float minDistance = 100000.0f;
  for (int i = 0; i < MAXSPAWNENEMIES; i++) {
    if (!enemyArr[i].active)
      continue;
    float temp = minDistance;

    destroyEnemy(&enemyArr[i], player);

    minDistance =
        fabs(fmin(calculateDistance(&enemyArr[i], player), minDistance));
    if (temp != minDistance) {
      indexOfEnemy = i;
    }
  }
  // checks if the player is in range
  Weapon weapon = player->weapon;
  if (minDistance <= weapon.range && enemyArr[indexOfEnemy].fakeHealth > 0) {
    return indexOfEnemy;
  }
  return -2;
}


float calculateDistance(Enemy *enemy, Player *player) {
  float dx = player->x - enemy->x;
  float dy = player->y - enemy->y;
  return sqrtf(dx * dx + dy * dy);
}


bool checkIfPlayerCanShoot(Player *player) {
  if (!player->canShoot && player->timer > 0) {
    player->timer--;
    return false;
  }
  if (player->timer <= 0) {
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

void updatePlayer(Player *player, Weapon *weaponArr) {
  playerMovement(player);
  drawPlayer(player);
  invTimer(player);
  updateWeapon(weaponArr, player);
}
