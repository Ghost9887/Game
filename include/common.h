#ifndef COMMON_H
#define COMMON_H

#include <stdbool.h>

#define SCREENWIDTH 1200
#define SCREENHEIGHT 800
#define MAXENEMIES 1000
#define MAXPROJECTILES 200
#define TARGETFPS 60 
#define MAXSPAWNENEMIES 40

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
  float speed;
  bool canShoot;
  float invTime;
  float timer;
  Weapon weapon;
} Player;

#endif
