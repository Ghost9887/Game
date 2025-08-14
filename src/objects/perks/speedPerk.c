#include "speedPerk.h"


Perk createSpeedPerk(){
  Perk perk;
  perk.x = 500;
  perk.y = 500;
  perk.data = 1.5f; 
  perk.type = "speed";
  perk.cost = 20;
  perk.consumed = false;
  return perk;
}
