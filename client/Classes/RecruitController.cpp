#include "RecruitController.h"
#include "PlayerModel.h"
#include "BattleModel.h"
#include "ObjectHolder.h"
#include "VehicleModel.h"
#include "FighterModel.h"
#include "FighterHolder.h"

 ErrorCode RecruitController::Recruit(PlayerModelPtr player)
{
    if (player->_battle != nullptr)
    {
        return ErrorCode::AlreadyRecruited;
    }

    BattleModelPtr battle(new BattleModel);
    FighterModelPtr fighter = GetObjectHolder<FighterHolder>(ActorType::Fighter).Find(FighterId(1));

    for (auto it : player->_vehicles)
    {
        VehicleModelPtr vehicle = it.second;

        float maxCapacity = 0;
        for (auto& cargo : vehicle->_cargos)
        {
            maxCapacity += cargo._capacity;
        }

        std::vector<FighterModelPtr> fighters;
        while (maxCapacity > 0)
        {
            fighters.push_back(fighter->Clone());
            maxCapacity -= fighter->_weight;
        }

        battle->_figher_map.insert(std::make_pair(vehicle, fighters));
    }

    player->_battle = battle;
    return ErrorCode::Success;
}
