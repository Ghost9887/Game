#include "basicEnemy.h"
#include <stdlib.h>

Enemy createBasicEnemy(float posX, float posY) {
  Enemy enemy;
  enemy.id = 0;
  enemy.x = posX;
  enemy.y = posY;
  enemy.width = 55;
  enemy.height = 64;
  enemy.health = 100;
  enemy.damage = 40;
  enemy.speed = 70.0f;
  enemy.money = 80;
  enemy.active = true;
  //animations
  enemy.currentFrame = 0;
  enemy.frameTime = 0.0f;
  enemy.frameSpeed = 0.1f; // seconds per frame
  // used for selecting the coordinates on the sprite sheet
  enemy.frameRec = (Rectangle){ 0.0f, 0.0f, 64.0f, 64.0f};
  return enemy;
}

