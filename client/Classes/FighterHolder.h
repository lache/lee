#ifndef __FighterHolder_H__
#define __FighterHolder_H__

#include "Typedefs.h"
#include "ObjectHolder.h"
#include "FighterModel.h"

class FighterHolder : public ModelHolder<FighterModel, FighterId>
{
public:
    virtual bool Initialize();
};

#endif
