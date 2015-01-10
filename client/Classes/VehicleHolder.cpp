#include "VehicleHolder.h"
#include "VehicleModel.h"
#include "ObjectHolderRegister.h"
#include "rapidjson/document.h"

REGISTER_OBJECT_HOLDER(ActorType::Vehicle, VehicleHolder);

bool VehicleHolder::Initialize()
{
    static const char* data = "[{\"id\":1,\"price\":170},{\"id\":2,\"price\":200},{\"id\":3,\"price\":230}]";

    rapidjson::Document doc;
    doc.Parse(data);

    // load templates
    for (rapidjson::SizeType i = 0; i < doc.Size(); ++i)
    {
        rapidjson::Value& each = doc[i];

        VehicleModelPtr vehicle(new VehicleModel);
        vehicle->_price = each["price"].GetInt();

        _modelMap.insert(std::make_pair(VehicleId(each["id"].GetInt()), vehicle));
    }
    return true;
}
