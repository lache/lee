#ifndef __ObjectHolder_H__
#define __ObjectHolder_H__

#include "Typedefs.h"
#include "ActorType.h"
#include <map>

class ObjectHolder
{
public:
    virtual bool Initialize() = 0;
};

class VehicleHolder : public ObjectHolder
{
public:
    virtual bool Initialize();

    VehicleModelPtr Find(VehicleId vehicleId)
    {
        return _vehicleMap[vehicleId];
    }

private:
    std::map<VehicleId, VehicleModelPtr> _vehicleMap;
};

class FighterHolder : public ObjectHolder
{
public:
    virtual bool Initialize();

    FighterModelPtr Find(FighterId vehicleId)
    {
        return _fighterMap[vehicleId];
    }

private:
    std::map<FighterId, FighterModelPtr> _fighterMap;
};

ObjectHolder* GetObjectHolderInternal(ActorType actorType);

template <typename HolderType>
inline HolderType& GetObjectHolder(ActorType actorType)
{
    ObjectHolder* holder = GetObjectHolderInternal(actorType);
    return *((HolderType*)holder);
}

#endif
