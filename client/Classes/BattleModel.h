#ifndef __BattleModel_H__
#define __BattleModel_H__

#include "Typedefs.h"
#include <vector>
#include <map>

class BattleModel
{
public:
    std::map<VehicleModelPtr, std::vector<FighterModelPtr>> _figher_map;
};

#endif
