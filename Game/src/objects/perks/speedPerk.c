#include "speedPerk.h"


Perk createSpeedPerk(){
  Perk perk;
  perk.id = 1;
  perk.data = 230.0f; 
  perk.type = "speed";
  perk.cost = 40;
  perk.consumed = false;
  return perk;
}
