#ifndef __BuyVehicleWindow_H__
#define __BuyVehicleWindow_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"
#include "Typedefs.h"

class BuyVehicleWindow : public cocos2d::ui::RelativeBox
{
public:
    static void open(LaneId laneId, const PlayerModelPtr& playerModel);
    static void close();
    static BuyVehicleWindow* create(LaneId laneId, const PlayerModelPtr& playerModel);

    void setLane(LaneId laneId) { _laneId = laneId; }
    LaneId getLane() const { return _laneId; }

CC_CONSTRUCTOR_ACCESS:
    virtual bool initWithLaneId(const cocos2d::Size& size, LaneId laneId, const PlayerModelPtr& playerModel);

private:
    BuyVehicleWindow();
    ~BuyVehicleWindow();

    static BuyVehicleWindow* s_ins;

    cocos2d::Node* createRootBox() const;
    cocos2d::Node* createWinTitle(const std::string& title) const;
    cocos2d::Node* createScrollView(const PlayerModelPtr& playerModel);
    cocos2d::Node* createScrollViewBox(const PlayerModelPtr& playerModel);
    cocos2d::Node* createVehicleButton(const VehicleId& vehicleId, const PlayerModelPtr& playerModel);
    cocos2d::Node* createCloseButton(const std::string& title);

    float sumContentSizeHeight(cocos2d::Node* node) const;

    LaneId _laneId;
};

#endif // __BuyVehicleWindow_H__
