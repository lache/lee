#ifndef __BuyVehicleWindow_H__
#define __BuyVehicleWindow_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"

class BuyVehicleWindow : public cocos2d::ui::RelativeBox
{
public:
    static void open(int laneId);
    static void close();
    static BuyVehicleWindow* create(int laneId);

    void setLane(int laneId) { _laneId = laneId; }
    int getLane() const { return _laneId; }

    static BuyVehicleWindow* s_ins;

CC_CONSTRUCTOR_ACCESS:
    virtual bool initWithLaneId(const cocos2d::Size& size, int laneId);

private:
    BuyVehicleWindow();
    ~BuyVehicleWindow();

    cocos2d::Node* createRootBox() const;
    cocos2d::Node* createWinTitle(const std::string& title) const;
    cocos2d::Node* createScrollView();
    cocos2d::Node* createScrollViewBox();
    cocos2d::Node* createVehicleButton(int vehicleId);
    cocos2d::Node* createCloseButton(const std::string& title);

    float sumContentSizeHeight(cocos2d::Node* node) const;

    int _laneId;
};

#endif // __BuyVehicleWindow_H__
