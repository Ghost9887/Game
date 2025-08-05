#ifndef COMMON_H
#define COMMON_H

#include <stdbool.h>

typedef struct {
  float x;
  float y;
  int width;
  int height;
  int health;
  int damage;
  bool active;
} Enemy;

typedef struct {
  float x;
  float y;
  float damage;
  int speed;
  int target;
  bool active;
  float lifetime;
  float size;
  bool explosive;
} Projectile;

typedef struct {
  int round;
  bool inBreak;
  float breakTimer;
} Round;

typedef struct {
  int coinCounter;
} Coins;

typedef struct {
  float x;
  float y;
  int width;
  int height;
  float damage;
  float range;
  float fireRate;
  char *type;
  bool holding;
} Weapon;

typedef struct {
  float x;
  float y;
  int width;
  int height;
  int health;
  bool canShoot;
  float invTime;
  float timer;
  Weapon weapon;
} Player;

#endif
