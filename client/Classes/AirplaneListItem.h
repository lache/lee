#ifndef __AIRPLANELISTITEM_H__
#define __AIRPLANELISTITEM_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class AirplaneListItem : public cocos2d::ui::Button
{
public:
	static AirplaneListItem* create(const std::string& filename, const std::string& text, int vehicleId);

    virtual void onEnter() override;

CC_CONSTRUCTOR_ACCESS:
	virtual bool init(const std::string& normalImage, const std::string& text, int vehicleId);
};

#endif // __AIRPLANELISTITEM_H__
