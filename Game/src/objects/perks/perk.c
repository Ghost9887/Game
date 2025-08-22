#include "perk.h"
#include "healthPerk.h"
#include "speedPerk.h"

void initPerkArr(Perk *perkArr){
  perkArr[0] = createHealthPerk();
  perkArr[1] = createSpeedPerk();
}
