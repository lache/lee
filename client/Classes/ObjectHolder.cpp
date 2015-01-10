#include "ObjectHolder.h"
#include "ObjectHolderRegister.h"
#include <unordered_map>
#include <cassert>

typedef std::unordered_map<ActorType, ObjectHolder*> ObjectHolderMap;

static inline ObjectHolderMap& GetObjectHolderMap()
{
    static ObjectHolderMap s_HolderMap;
    return s_HolderMap;
}

void RegisterObjectHolder(ActorType actorType, ObjectHolder* holder)
{
    GetObjectHolderMap().insert(std::make_pair(actorType, holder));
}

ObjectHolder* GetObjectHolderInternal(ActorType actorType)
{
    auto it = GetObjectHolderMap().find(actorType);
    if (it != GetObjectHolderMap().end())
        return it->second;

    assert(false);
    return nullptr;
}
