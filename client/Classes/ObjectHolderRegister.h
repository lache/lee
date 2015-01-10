#ifndef __ObjectHolderRegister_H__
#define __ObjectHolderRegister_H__

#include "Typedefs.h"
#include "ActorType.h"
#include "ObjectHolder.h"

void RegisterObjectHolder(ActorType actorType, ObjectHolder* holder);

#define REGISTER_OBJECT_HOLDER(actorType, holderTypeName) \
    struct __init_##holderTypeName { \
        __init_##holderTypeName() { \
            ObjectHolder* holder = new holderTypeName;\
            holder->Initialize(); \
            RegisterObjectHolder(actorType, holder); \
        } \
    } ___init_var_##holderTypeName


#endif
