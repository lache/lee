#include "ResourceBar.h"

#include "TouchableSprite.h"
#include "FontSize.h"
#include "PlayerModel.h"
#include "CheatWindow.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;

ResourceBar* ResourceBar::s_ins;

ResourceBar* ResourceBar::create(const PlayerModelPtr& playerModel)
{
    ResourceBar *btn = new (std::nothrow) ResourceBar;
    if (btn && btn->initWithPlayer(playerModel))
    {
        btn->autorelease();
        s_ins = btn;
        return btn;
    }
    CC_SAFE_DELETE(btn);
    return nullptr;
}

bool ResourceBar::initWithPlayer(const PlayerModelPtr& playerModel)
{
    if (Button::init("images/MagentaSquareSmall.png") == false)
        return false;

    _playerModel = playerModel;

    setName("ResourceBar");
    setScale9Enabled(true);
    setTitleFontSize(FontSize::getSmall());
    setTitleColor(Color3B::BLACK);

    addClickEventListener([this](Ref* sender)
    {
        CheatWindow::open(_playerModel);
    });

    return true;
}

void ResourceBar::updateGold()
{
    setTitleText(StringUtils::format("GOLD %d", _playerModel == nullptr ? 0 : _playerModel->_gold));
}
