#include "BattleController.h"
#include "FighterModel.h"

long long int BattleController::CalculateGold(std::vector<FighterModelPtr>&& enemyFighters)
{
    double gainPoint = 0;
    for (const auto& enemyFighter : enemyFighters)
    {
        gainPoint += enemyFighter->_maxHp;
    }
    return static_cast<long long int>(gainPoint);
}

