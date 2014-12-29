#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* scene();
    
    // a selector callback
    void menuCloseCallback(Ref* sender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);

	void setLaneButtonString(int laneId, const std::string& text) const;

	void updateResBar() const;

private:
	void createBattleButton();

	class BuyAirplaneWindow* _buyAirplaneWindow;
	class ResourceBar* _resBar;
	cocos2d::Node* _laneButtonGroup;
};

#endif // __HELLOWORLD_SCENE_H__
