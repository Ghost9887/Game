#include "healthPerk.h"


Perk createHealthPerk(){
  Perk perk;
  perk.id = 0;
  perk.data = 150; 
  perk.type = "health";
  perk.cost = 20;
  perk.consumed = false;
  return perk;
}
