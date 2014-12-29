#ifndef __LaneListItem_H__
#define __LaneListItem_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class LaneListItem : public cocos2d::ui::Button
{
public:
	static LaneListItem* create(const std::string& filename, const std::string& text);

	void setString(const std::string& text);

CC_CONSTRUCTOR_ACCESS:
	virtual bool init(const std::string& normalImage, const std::string& text);

private:
	
	cocos2d::Label* _label;
};

#endif // __LaneListItem_H__
