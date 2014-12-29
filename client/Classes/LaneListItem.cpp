#include "LaneListItem.h"
#include "TouchableSprite.h"
#include "FontSize.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;

// on "init" you need to initialize your instance
LaneListItem* LaneListItem::create(const std::string& filename, const std::string& text)
{
	LaneListItem *btn = new (std::nothrow) LaneListItem;
	if (btn && btn->init(filename, text))
	{
		btn->autorelease();
		return btn;
	}
	CC_SAFE_DELETE(btn);
	return nullptr;
}

bool LaneListItem::init(const std::string& normalImage, const std::string& text)
{
	bool ret = true;
	ret = Button::init(normalImage);

    _label = Label::createWithSystemFont(text, "Arial", FontSize::getNormal());
	_label->setColor(Color3B::BLACK);
	_label->setNormalizedPosition(Vec2::ANCHOR_MIDDLE);
	addChild(_label);

	return ret;
}

void LaneListItem::setString(const std::string& text)
{
	_label->setString(text);
}
