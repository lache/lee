#include "ResourceBar.h"
#include "Player.h"
#include "TouchableSprite.h"
#include "FontSize.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;

// on "init" you need to initialize your instance
ResourceBar* ResourceBar::create()
{
    ResourceBar *btn = new (std::nothrow) ResourceBar;
    if (btn && btn->init())
    {
        btn->autorelease();
        return btn;
    }
    CC_SAFE_DELETE(btn);
    return nullptr;
}

bool ResourceBar::init()
{
    setName("ResourceBar");

    _background = Sprite::create("Images/MagentaSquare.png");
    _background->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
    _background->setNormalizedPosition(Vec2::ANCHOR_MIDDLE_TOP);
    addChild(_background);

    _label = Label::createWithSystemFont("GOLD 0", "Arial", FontSize::getSmall());
    _label->setColor(Color3B::BLACK);
    _label->setNormalizedPosition(Vec2::ANCHOR_MIDDLE);
    addChild(_label);

    return true;
}

void ResourceBar::updateSize()
{
    _background->setScaleX(getContentSize().width / _background->getContentSize().width);
    _background->setScaleY(getContentSize().height / _background->getContentSize().height);
}

void ResourceBar::updateGold() const
{
    _label->setString(StringUtils::format("GOLD %d", Player::gold));
}

void ResourceBar::onEnter()
{
    Node::onEnter();

    updateSize();
}
