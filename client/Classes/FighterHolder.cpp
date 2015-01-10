#include "FighterHolder.h"
#include "FighterModel.h"
#include "ObjectHolderRegister.h"

REGISTER_OBJECT_HOLDER(ActorType::Fighter, FighterHolder);

bool FighterHolder::Initialize()
{
    // load templates
    return true;
}
