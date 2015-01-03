#ifndef __BuyControlller_H__
#define __BuyControlller_H__

#include "Typedefs.h"
#include "ErrorCode.h"

class BuyController
{
public:
    static ErrorCode BuyVehicle(PlayerModelPtr player, LaneId laneId, VehicleId vehicleId);
};

#endif
