#ifndef _LobbyScene_H_
#define _LobbyScene_H_

#include "cocos2d.h"
#include "Typedefs.h"

class LobbyLayer : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene(const PlayerModelPtr& playerModel);

    bool initWithPlayer(const PlayerModelPtr& playerModel);

    void menuCloseCallback(cocos2d::Ref* pSender);

    void setLaneButtonString(LaneId laneId, const std::string& text) const;

    void updateResBar() const;

CC_CONSTRUCTOR_ACCESS:
    static LobbyLayer* create(const PlayerModelPtr& playerModel);

private:
    LobbyLayer();

    class BuyVehicleWindow* _buyAirplaneWindow;
    class ResourceBar* _resBar;
    cocos2d::Node* _laneButtonGroup;

    PlayerModelPtr _playerModel;
};

#endif // _LobbyScene_H_
