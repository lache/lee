#include "ObjectHolder.h"
#include "VehicleModel.h"
#include "rapidjson/document.h"

bool VehicleHolder::Initialize()
{
    static const char* data = "[{\"id\":1,\"price\":170},{\"id\":2,\"price\":200},{\"id\":3,\"price\":2300}]";

    rapidjson::Document doc;
    doc.Parse(data);

    // load templates
    for (rapidjson::SizeType i = 0; i < doc.Size(); ++i)
    {
        rapidjson::Value& each = doc[i];

        VehicleModelPtr vehicle(new VehicleModel);
        vehicle->_price = each["price"].GetInt();

        _vehicleMap.insert(std::make_pair(VehicleId(each["id"].GetInt()), vehicle));
    }
    return true;
}

bool FighterHolder::Initialize()
{
    // load templates
    return true;
}

ObjectHolder* GetObjectHolderInternal(ActorType actorType)
{
    static std::map<ActorType, ObjectHolder*> s_HolderMap;
    auto it = s_HolderMap.find(actorType);
    if (it != s_HolderMap.end())
        return it->second;

    ObjectHolder* holder;
    switch (actorType)
    {
    case ActorType::Vehicle: holder = new VehicleHolder; break;
    case ActorType::Fighter: holder = new FighterHolder; break;
    }

    holder->Initialize();
    s_HolderMap.insert(std::make_pair(actorType, holder));

    return holder;
}
