#include "RecruitButton.h"
#include "TouchableSprite.h"
#include "LobbyLayer.h"
#include "Player.h"
#include "BuyAirplaneWindow.h"
#include "SimplePopup.h"
#include "FontSize.h"
#include "RecruitContext.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;

RecruitButton::RecruitButton()
    : _currentRecruitSize(0)
{
}

RecruitButton* RecruitButton::create(const Size& size, std::shared_ptr<RecruitContext> recruitContext)
{
	RecruitButton *btn = new (std::nothrow) RecruitButton;
    if (btn && btn->init(size, recruitContext))
	{
		btn->autorelease();
		return btn;
	}
	CC_SAFE_DELETE(btn);
	return nullptr;
}

bool RecruitButton::init(const Size& size, std::shared_ptr<RecruitContext> recruitContext)
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

        recruitContext->setRecruitButton(this);
        recruitContext->startRecruit(root, 20);
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
