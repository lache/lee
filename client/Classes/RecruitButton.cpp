#include "RecruitButton.h"
#include "TouchableSprite.h"
#include "LobbyLayer.h"
#include "BuyVehicleWindow.h"
#include "SimplePopup.h"
#include "FontSize.h"
#include "PlayerModel.h"
#include "RecruitController.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;

RecruitButton::RecruitButton()
    : _currentRecruitSize(0)
{
}

RecruitButton* RecruitButton::create(const Size& size, const PlayerModelPtr& playerModel)
{
	RecruitButton *btn = new (std::nothrow) RecruitButton;
    if (btn && btn->init(size, playerModel))
	{
		btn->autorelease();
		return btn;
	}
	CC_SAFE_DELETE(btn);
	return nullptr;
}

bool RecruitButton::init(const Size& size, const PlayerModelPtr& playerModel)
{
    if (Button::init("images/RecruitButton.png") == false)
        return false;

    setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
    setNormalizedPosition(Vec2::ANCHOR_MIDDLE_BOTTOM);
    setTitleColor(Color3B::BLACK);
    setTitleFontSize(FontSize::getSmall());
    setScale9Enabled(true);
    setContentSize(size);
    setButtonState(ButtonState::CAN_RECRUIT);

    addClickEventListener([=](Ref* sender)
    {
        setButtonState(ButtonState::RECRUIT_IN_PROGRESS, _currentRecruitSize);
        
        auto director = Director::getInstance();
        auto root = director->getRunningScene()->getChildByName<LobbyLayer*>("LobbyLayer");
        auto recruitGround = root->getChildByName("RecruitGround");
        if (recruitGround == nullptr)
        {
            recruitGround = Node::create();
            root->addChild(recruitGround);
        }

        RecruitController::Recruit(playerModel);
    });

    return true;
}

void RecruitButton::setButtonState(ButtonState state, int currentRecruitSize)
{
    _currentRecruitSize = currentRecruitSize;

    switch (state)
    {
    default:
    case ButtonState::CAN_RECRUIT:
        setTitleText(StringUtils::format("Recruit\n%d", currentRecruitSize));
        setEnabled(true);
        setColor(Color3B::WHITE);
        break;
    case ButtonState::RECRUIT_IN_PROGRESS:
        startBlinkAction();
        setTitleText(StringUtils::format("Recruit In Progress\n%d", currentRecruitSize));
        setEnabled(false);
        //setColor(Color3B::GRAY);
        break;
    }
}

void RecruitButton::startBlinkAction()
{
    stopActionByTag(1);

    const auto duration = 0.06f;

    auto damageTint1 = TintTo::create(duration, 200, 200, 200);
    auto damageTint2 = TintTo::create(duration, 255, 255, 255);
    auto damageTint = Sequence::create(damageTint1, damageTint2, nullptr);
    
    auto scaleTo1 = ScaleTo::create(duration, 1.1f, 1.1f, 1.1f);
    auto scaleTo2 = ScaleTo::create(duration, 1.0f, 1.0f, 1.0f);
    auto scale = Sequence::create(scaleTo1, scaleTo2, nullptr);

    damageTint->setTag(1);
    scale->setTag(1);

    runAction(damageTint);
    runAction(scale);
}
