#ifndef _LobbyScene_H_
#define _LobbyScene_H_

#include "cocos2d.h"
#include "Typedefs.h"

class RecruitContext;

class LobbyLayer : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene(const PlayerModelPtr& playerModel);

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    bool initWithPlayer(const PlayerModelPtr& playerModel);

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    void setLaneButtonString(LaneId laneId, const std::string& text) const;

    void updateResBar() const;

CC_CONSTRUCTOR_ACCESS:
    static LobbyLayer* create(const PlayerModelPtr& playerModel);

private:
    LobbyLayer();

    void createBattleButton();

    class BuyVehicleWindow* _buyAirplaneWindow;
    class ResourceBar* _resBar;
    cocos2d::Node* _laneButtonGroup;

    std::shared_ptr<RecruitContext> _recruitContext;
    PlayerModelPtr _playerModel;
};

#endif // _LobbyScene_H_
