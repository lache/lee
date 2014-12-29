#include "AirplaneListItem.h"
#include "TouchableSprite.h"
#include "LobbyLayer.h"
#include "Player.h"
#include "BuyAirplaneWindow.h"
#include "SimplePopup.h"
#include "FontSize.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;

// on "init" you need to initialize your instance
AirplaneListItem* AirplaneListItem::create(const std::string& filename, const std::string& text, int vehicleId)
{
	AirplaneListItem *btn = new (std::nothrow) AirplaneListItem;
	if (btn && btn->init(filename, text, vehicleId))
	{
		btn->autorelease();
		return btn;
	}
	CC_SAFE_DELETE(btn);
	return nullptr;
}

bool AirplaneListItem::init(const std::string& normalImage, const std::string& text, int vehicleId)
{
	bool ret = true;
	ret = Button::init(normalImage);

    setScale9Enabled(true);

    setTitleColor(Color3B::BLACK);
    setTitleText(text);
    setTitleFontSize(FontSize::getSmall());

	addClickEventListener([this, vehicleId](Ref* sender)
	{
		CCLOG("Vehicle ID %d clicked, position = (%f, %f)", vehicleId, getPosition().x, getPosition().y);

		auto director = Director::getInstance();
		auto root = director->getRunningScene()->getChildByName<LobbyLayer*>("LobbyLayer");

		auto price = 100;
		if (Player::gold < price)
		{
			auto popup = SimplePopup::create("** Insufficient funds **", Color4B::RED);
			popup->runAction(Sequence::create(DelayTime::create(1), FadeOut::create(0.3f), RemoveSelf::create(), nullptr));

			root->addChild(popup);
		}
		else
		{
			Player::gold -= 100;

            auto buttonText = StringUtils::format("Air %d", vehicleId);
			root->setLaneButtonString(BuyAirplaneWindow::s_ins->getLane(), buttonText);

			root->updateResBar();

            BuyAirplaneWindow::s_ins->setVisible(false);
		}
	});

	return ret;
}

void AirplaneListItem::onEnter()
{
    setContentSize(Size(getParent()->getContentSize().width, _titleRenderer->getContentSize().height));
    //setContentSize(Size(getParent()->getContentSize().width, _label->getContentSize().height));

    //setScaleX(getParent()->getContentSize().width / getContentSize().width);// , getParent()->getContentSize().height / getContentSize().height));

    Button::onEnter();
}