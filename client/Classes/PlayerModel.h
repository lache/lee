#ifndef __PlayerModel_H__
#define __PlayerModel_H__

#include "Typedefs.h"
#include <map>

class PlayerModel
{
public:
    std::map<LaneId, VehicleModelPtr> _vehicles;
    long long int _gold;
    long long int _reputation;

    std::string _name;

    BattleModelPtr _battle;
};

#endif
