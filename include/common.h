#ifndef COMMON_H
#define COMMON_H

#include <stdbool.h>
#include "raylib.h"

#define SCREENWIDTH 1200
#define SCREENHEIGHT 800
#define MAXPROJECTILES 200
#define TARGETFPS 60 
#define MAXSPAWNENEMIES 40
#define MAXPICKUPS 10
#define MAXWEAPONS 3

typedef struct {
  float x;
  float y;
  int width;
  int height;
  float health;
  float speed;
  int damage;
  bool active;
} Enemy;

typedef struct {
  float x;
  float y;
  Vector2 previousPos;
  float dX;
  float dY;
  float damage;
  float speed;
  int target;
  bool active;
  float lifetime;
  float size;
} Projectile;

typedef struct {
  int round;
  bool inBreak;
  float breakTimer;
} Round;

typedef struct {
  int id;
  float x;
  float y;
  int width;
  int height;
  float rotation;
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
  char *name;
  int weaponCost;
  int ammoCost;
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

typedef struct{
  float x;
  float y;
  Weapon *weapon;
  int weaponCost;
  int ammoCost;
}WeaponBuy;

#endif
