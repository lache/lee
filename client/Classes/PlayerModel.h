#ifndef __PlayerModel_H__
#define __PlayerModel_H__

#include "Typedefs.h"
#include <map>

class PlayerModel
{
public:
    PlayerModel()
        : _gold(0)
        , _reputation(0)
    {}

public:
    std::map<LaneId, VehicleModelPtr> _vehicles;
    long long int _gold;
    long long int _reputation;

    std::string _name;

    BattleModelPtr _battle;
    RecruitModelPtr _recruit;
};

#endif
