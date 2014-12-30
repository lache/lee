#ifndef _LobbyScene_H_
#define _LobbyScene_H_

#include "cocos2d.h"

class RecruitContext;

class LobbyLayer : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(LobbyLayer);

    void setLaneButtonString(int laneId, const std::string& text) const;

    void updateResBar() const;

private:
    LobbyLayer();

    void createBattleButton();

    class BuyAirplaneWindow* _buyAirplaneWindow;
    class ResourceBar* _resBar;
    cocos2d::Node* _laneButtonGroup;

    std::shared_ptr<RecruitContext> _recruitContext;
};

#endif // _LobbyScene_H_
