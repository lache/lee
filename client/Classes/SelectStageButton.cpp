#include "SelectStageButton.h"
#include "TouchableSprite.h"
#include "LobbyLayer.h"
#include "Player.h"
#include "BuyVehicleWindow.h"
#include "SimplePopup.h"
#include "FontSize.h"
#include "RecruitContext.h"
#include "SelectStageWindow.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;

SelectStageButton::SelectStageButton()
{
}

SelectStageButton* SelectStageButton::create(const Size& size, const std::shared_ptr<RecruitContext>& recruitContext)
{
	SelectStageButton *btn = new (std::nothrow) SelectStageButton;
    if (btn && btn->init(size, recruitContext))
	{
		btn->autorelease();
		return btn;
	}
	CC_SAFE_DELETE(btn);
	return nullptr;
}

bool SelectStageButton::init(const Size& size, const std::shared_ptr<RecruitContext>& recruitContext)
{
    if (Button::init("images/SelectStageButton.png") == false)
        return false;

    setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
    /*setNormalizedPosition(Vec2::ANCHOR_MIDDLE_BOTTOM);*/
    setTitleColor(Color3B::BLACK);
    setTitleFontSize(FontSize::getSmall());
    setScale9Enabled(true);
    setContentSize(size);
    setButtonState(ButtonState::CANNOT_SELECT_STAGE);

    recruitContext->setSelectStageButton(this);
    
    addClickEventListener([=](Ref* sender)
    {
        SelectStageWindow::open(recruitContext);
    });

    return true;
}

void SelectStageButton::setButtonState(ButtonState state, int currentRecruitSize)
{
    switch (state)
    {
    default:
    case ButtonState::CANNOT_SELECT_STAGE:
        setTitleText(StringUtils::format("Not Enough Fighters"));
        setEnabled(false);
        setColor(Color3B::WHITE);
        break;
    case ButtonState::CAN_SELECT_STAGE:
        startBlinkAction();
        setTitleText(StringUtils::format("Select Stage"));
        setEnabled(true);
        break;
    }
}

void SelectStageButton::startBlinkAction()
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
