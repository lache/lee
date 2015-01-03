#ifndef __ObjectHolder_H__
#define __ObjectHolder_H__

#include "Typedefs.h"
#include "ActorType.h"
#include "VehicleModel.h"
#include <map>

class ObjectHolder
{
public:
    virtual bool Initialize() = 0;
};

class VehicleHolder : public ObjectHolder
{
public:
    virtual bool Initialize()
    {
        // load templates
        _vehicleMap[VehicleId(1)] = VehicleModelPtr(new VehicleModel);
        _vehicleMap[VehicleId(2)] = VehicleModelPtr(new VehicleModel);
        _vehicleMap[VehicleId(3)] = VehicleModelPtr(new VehicleModel);

        _vehicleMap[VehicleId(1)]->_price = 170;
        _vehicleMap[VehicleId(2)]->_price = 200;
        _vehicleMap[VehicleId(3)]->_price = 230;

        return true;
    }
    VehicleModelPtr Find(VehicleId vehicleId)
    {
        return _vehicleMap[vehicleId];
    }
    std::map<VehicleId, VehicleModelPtr> _vehicleMap;
};

class FighterHolder : public ObjectHolder
{
public:
    virtual bool Initialize()
    {
        // load templates
        return true;
    }
    FighterModelPtr Find(FighterId vehicleId)
    {
        return _fighterMap[vehicleId];
    }
    std::map<FighterId, FighterModelPtr> _fighterMap;
};


template <typename HolderType>
inline HolderType& GetObjectHolder(ActorType actorType)
{
    static std::map<ActorType, ObjectHolder*> s_HolderMap;
    auto it = s_HolderMap.find(actorType);
    if (it != s_HolderMap.end())
        return *((HolderType*)it->second);

    ObjectHolder* holder;
    switch (actorType)
    {
    case ActorType::Vehicle: holder = new VehicleHolder; break;
    case ActorType::Fighter: holder = new FighterHolder; break;
    }

    holder->Initialize();
    s_HolderMap.insert(std::make_pair(actorType, holder));

    return *((HolderType*)holder);
}

#endif
