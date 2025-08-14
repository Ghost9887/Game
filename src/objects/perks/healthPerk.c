#include "healthPerk.h"


Perk createHealthPerk(){
  Perk perk;
  perk.x = 400;
  perk.y = 500;
  perk.data = 150; 
  perk.type = "health";
  perk.cost = 20;
  perk.consumed = false;
  return perk;
}
