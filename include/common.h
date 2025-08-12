#ifndef COMMON_H
#define COMMON_H

#include <stdbool.h>
#include "raylib.h"

#define SCREENWIDTH 1200
#define SCREENHEIGHT 800
#define MAXENEMIES 800
#define MAXPROJECTILES 200
#define TARGETFPS 60 
#define MAXSPAWNENEMIES 40
#define MAXPICKUPS 10

typedef struct {
  float x;
  float y;
  int width;
  int height;
  float health;
  float fakeHealth;
  float speed;
  int damage;
  bool active;
} Enemy;

typedef struct {
  float x;
  float y;
  float damage;
  float speed;
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
  float x;
  float y;
  int width;
  int height;
  float damage;
  float range;
  float fireRate;
  float projectileSpeed;
  int maxMagSize;
  int maxReserveSize;
  int currentMagSize;
  int currentReserveSize;
  float reloadTime;
  float reloadTimer;
  char *type;
  bool holding;
} Weapon;

typedef struct {
  float x;
  float y;
  int width;
  int height;
  int health;
  int money;
  float speed;
  bool canShoot;
  float invTime;
  float timer;
  Weapon *weapon;
} Player;

typedef struct{
  float x;
  float y;
  int data;
  Color colour;
  bool active;
  float lifetime;
  char *type;
} Pickup;

#endif
