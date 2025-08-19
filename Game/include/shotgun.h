#ifndef SHOTGUN_H
#define SHOTGUN_H

  #include "raylib.h"
  #include "common.h"
  
  Weapon createShotgun();
  void spreadShot(Projectile *projectileArr, Player *player);

#endif
