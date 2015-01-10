#ifndef __Typedefs_H__
#define __Typedefs_H__

#include "Id.h"
#include <memory>

#define ID_NAME(typeName) typeName##Id
#define DECLARE_ID_TYPE(typeName, valueType) \
    typedef Id<IdType::typeName, valueType> ID_NAME(typeName)

DECLARE_ID_TYPE(Lane, int);
DECLARE_ID_TYPE(Vehicle, int);
DECLARE_ID_TYPE(Fighter, int);

#undef DECLARE_ID_TYPE

#define DECLARE_SHARED_PTR(className) \
    class className; \
    typedef std::shared_ptr<className> className##Ptr

DECLARE_SHARED_PTR(ActorModel);
DECLARE_SHARED_PTR(CargoModel);
DECLARE_SHARED_PTR(VehicleModel);
DECLARE_SHARED_PTR(FighterModel);
DECLARE_SHARED_PTR(PlayerModel);
DECLARE_SHARED_PTR(RecruitModel);
DECLARE_SHARED_PTR(BattleModel);

#undef DECLARE_SHARED_PTR

#endif
