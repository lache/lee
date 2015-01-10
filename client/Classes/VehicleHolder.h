#ifndef __VehicleHolder_H__
#define __VehicleHolder_H__

#include "Typedefs.h"
#include "ObjectHolder.h"
#include "VehicleModel.h"

class VehicleHolder : public ModelHolder<VehicleModel, VehicleId>
{
public:
    virtual bool Initialize();
};

#endif