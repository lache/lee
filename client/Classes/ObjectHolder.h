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

template <typename ModelType, typename ModelIdType>
class ModelHolder : public ObjectHolder
{
public:
    typedef ModelIdType IdType;
    typedef std::shared_ptr<ModelType> PointerType;

    PointerType Find(IdType modelId) const
    {
        auto it = _modelMap.find(modelId);
        return it != _modelMap.end() ? it->second : PointerType();
    }

protected:
    std::map<IdType, PointerType> _modelMap;
};

ObjectHolder* GetObjectHolderInternal(ActorType actorType);

template <typename HolderType>
inline HolderType& GetObjectHolder(ActorType actorType)
{
    ObjectHolder* holder = GetObjectHolderInternal(actorType);
    return *((HolderType*)holder);
}

#endif
