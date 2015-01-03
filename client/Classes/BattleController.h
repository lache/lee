#ifndef __BattleController_H__
#define __BattleController_H__

#include "Typedefs.h"
#include <vector>

class BattleController
{
public:
    static long long int CalculateGold(std::vector<FighterModelPtr>&& fighters);
};

#endif
