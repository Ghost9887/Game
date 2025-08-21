#ifndef COMMON_H
#define COMMON_H

#include <stdbool.h>
#include "raylib.h"

#define SCREENWIDTH 1300 
#define SCREENHEIGHT 900 
#define MAXPROJECTILES 200
#define TARGETFPS 60 
#define MAXSPAWNENEMIES 40
#define MAXPICKUPS 10
#define MAXWEAPONS 3
#define MAXTILES 49284
#define MAXWEAPONBUYS 50

typedef struct {
  int id;
  float x;
  float y;
  int width;
  int height;
  float health;
  float speed;
  int damage;
  int money;
  bool active;
  int currentFrame;
  float frameTime;
  float frameSpeed;
  Rectangle frameRec;
} Enemy;

typedef struct {
  float x;
  float y;
  Vector2 previousPos;
  float dX;
  float dY;
  float damage;
  float speed;
  float range;
  float length;
  float distanceTraveled;
  int target;
  bool active;
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
  float scale;
  int spread;
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
  float weight;
  int currentFrame;
  float frameTime;
  float frameSpeed;
  Rectangle frameRec;
} Weapon;

typedef struct {
  float x;
  float y;
  int width;
  int height;
  float rotation;
  int health;
  int maxHealth;
  int money;
  float speed;
  float maxSpeed;
  bool canShoot;
  float invTime;
  float timer;
  Weapon *weapon;
  int currentFrame;
  float frameTime;
  float frameSpeed;
  Rectangle frameRec;
  bool ads;
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
  int x;
  int y;
  Weapon *weapon;
  int weaponCost;
  int ammoCost;
}WeaponBuy;

typedef struct{
  float x;
  float y;
  float data;
  char *type;
  int cost;
  bool consumed;  
}Perk;

typedef struct{
  int id;
  int x;
  int y;
  int width;
  int height;
  Texture2D texture;
}Tile;

typedef struct{
  int id;
  int startIndex;
  Rectangle rec;
}Chunk;

#endif
