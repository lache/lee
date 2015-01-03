#include "BuyController.h"
#include "PlayerModel.h"
#include "ActorModel.h"
#include "ObjectHolder.h"
#include "VehicleModel.h"

ErrorCode BuyController::BuyVehicle(PlayerModelPtr player, LaneId laneId, VehicleId vehicleId)
{
    VehicleModelPtr vehicle = GetObjectHolder<VehicleHolder>(ActorType::Vehicle).Find(vehicleId);
    if (player->_gold < vehicle->_price)
    {
        return ErrorCode::NoGold;
    }

    if (player->_vehicles[laneId] == nullptr)
    {
        return ErrorCode::LaneNotEmpty;
    }

    player->_vehicles[laneId] = vehicle->Clone();
    return ErrorCode::Success;
}
