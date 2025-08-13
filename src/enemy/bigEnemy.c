#include "bigEnemy.h"


Enemy createBigEnemy(float posX, float posY){
  Enemy enemy;
  enemy.x = posX;
  enemy.y = posY;
  enemy.width = 50;
  enemy.height = 80;
  enemy.health = 600;
  enemy.damage = 70;
  enemy.speed = 50.0f;
  enemy.active = true;
  return enemy;
}

