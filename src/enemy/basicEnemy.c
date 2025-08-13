#include "basicEnemy.h"
#include <stdlib.h>

Enemy createBasicEnemy(float posX, float posY) {
  Enemy enemy;
  enemy.x = posX;
  enemy.y = posY;
  enemy.width = 30;
  enemy.height = 50;
  enemy.health = 100;
  enemy.damage = 40;
  enemy.speed = 70.0f;
  enemy.active = true;
  return enemy;
}

