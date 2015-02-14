#ifndef __BattleModel_H__
#define __BattleModel_H__

#include "Typedefs.h"
#include <vector>
#include <map>

class Actor;

class BattleModel
{
public:
    StageId _stageId;
    std::map<VehicleModelPtr, std::vector<FighterModelPtr>> _fighter_map;
    std::vector<FighterModelPtr> _enemy_map;

    int _team1Size;
    int _team2Size;
    void setTeamSize(int team1, int team2);
    void onActorDead(Actor* a);
    void onTeam1Eliminated();
    void onTeam2Eliminated();

    BattleModel();
    ~BattleModel();
};

#endif
