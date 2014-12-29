#include "ResourceBar.h"
#include "Player.h"
#include "TouchableSprite.h"
#include "FontSize.h"
#include "CheatWindow.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;

ResourceBar* ResourceBar::s_ins;

ResourceBar* ResourceBar::create()
{
    ResourceBar *btn = new (std::nothrow) ResourceBar;
    if (btn && btn->init())
    {
        btn->autorelease();
        s_ins = btn;
        return btn;
    }
    CC_SAFE_DELETE(btn);
    return nullptr;
}

bool ResourceBar::init()
{
    if (Button::init("images/MagentaSquareSmall.png") == false)
        return false;

    setName("ResourceBar");
    setScale9Enabled(true);
    setTitleFontSize(FontSize::getSmall());
    setTitleColor(Color3B::BLACK);

    addClickEventListener([](Ref* sender)
    {
        CheatWindow::open();
    });

    return true;
}

void ResourceBar::updateGold()
{
    setTitleText(StringUtils::format("GOLD %d", Player::gold));
}
