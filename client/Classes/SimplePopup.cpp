#include "SimplePopup.h"
#include "TouchableSprite.h"

#include "Player.h"
#include "BuyVehicleWindow.h"
#include "FontSize.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;

SimplePopup* SimplePopup::create(const std::string& text, const Color4B& bgColor)
{
	SimplePopup *btn = new (std::nothrow) SimplePopup;
	if (btn && btn->init(text, bgColor))
	{
		btn->autorelease();
		return btn;
	}
	CC_SAFE_DELETE(btn);
	return nullptr;
}

bool SimplePopup::init(const std::string& text, const Color4B& bgColor)
{
	bool ret = true;

	ret = LayerColor::initWithColor(bgColor, 50, 25);
	if (ret == false)
		return false;

	setCascadeOpacityEnabled(true);

	_label = Label::createWithSystemFont(text, "Arial", FontSize::getNormal());
	_label->setColor(Color3B::WHITE);
	_label->setNormalizedPosition(Vec2::ANCHOR_MIDDLE);
	addChild(_label);

	setContentSize(_label->getContentSize());

	return ret;
}

void SimplePopup::onEnter()
{
	LayerColor::onEnter();

	setPosition(Vec2(getParent()->getContentSize().width / 2 - getContentSize().width / 2, getParent()->getContentSize().height - 2 * getContentSize().height));
	//setNormalizedPosition(Vec2::ANCHOR_TOP_LEFT);
}
