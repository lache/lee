#include "LobbyLayer.h"
#include "LaneListItem.h"
#include "BattleLayer.h"
#include "ResourceBar.h"
#include "BuyVehicleWindow.h"
#include "FontSize.h"
#include "PopText.h"
#include "RecruitContext.h"
#include "RecruitButton.h"
#include "SelectStageButton.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace cocos2d::ui;

LobbyLayer::LobbyLayer()
    : _recruitContext(new RecruitContext)
{
}

LobbyLayer* LobbyLayer::create(const PlayerModelPtr& playerModel)
{
    auto layer = new (std::nothrow) LobbyLayer;
    if (layer && layer->initWithPlayer(playerModel))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

Scene* LobbyLayer::createScene(const PlayerModelPtr& playerModel)
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = LobbyLayer::create(playerModel);

    layer->setName("LobbyLayer");

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LobbyLayer::initWithPlayer(const PlayerModelPtr& playerModel)
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }

    _playerModel = playerModel;

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto baseNode = Node::create();
    baseNode->setContentSize(visibleSize);
    baseNode->setPosition(origin);
    addChild(baseNode);

    // 배경 이미지
    auto sprite = Sprite::create("images/title2.png");
    sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
    sprite->setScale(visibleSize.height / sprite->getContentSize().height);
    sprite->setNormalizedPosition(Vec2::ANCHOR_MIDDLE_TOP);
    baseNode->addChild(sprite);

    // 자원 표시 상단 바
    _resBar = ResourceBar::create(_playerModel);
    _resBar->setContentSize(Size(visibleSize.width, FontSize::getSmall()));
    _resBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
    _resBar->setNormalizedPosition(Vec2::ANCHOR_MIDDLE_TOP);
    _resBar->updateGold();
    baseNode->addChild(_resBar);

    // 새 탈것 추가 버튼
    auto newPlaneButtonGroup = Node::create();
    newPlaneButtonGroup->setNormalizedPosition(Vec2(0, 1.0f/3));
    newPlaneButtonGroup->setContentSize(Size(baseNode->getContentSize().width, baseNode->getContentSize().height / 6));
    baseNode->addChild(newPlaneButtonGroup);

    for (auto i = 0; i < 4; ++i)
    {
        auto sprite = LaneListItem::create("images/CyanSquare.png", "E");
        sprite->addClickEventListener([this, i, baseNode](Ref* sender)
        {
            //CCLOG(("Click " + std::to_string(i)).c_str());

            BuyVehicleWindow::open(LaneId(i), _playerModel);
        });
        sprite->setAnchorPoint(Vec2::ZERO);
        sprite->setScaleX(newPlaneButtonGroup->getContentSize().width / sprite->getContentSize().width / 4);
        sprite->setScaleY(newPlaneButtonGroup->getContentSize().height / sprite->getContentSize().height);
        sprite->setPosition(Vec2(newPlaneButtonGroup->getContentSize().width / 4 * i, 0));
        newPlaneButtonGroup->addChild(sprite);
    }
    _laneButtonGroup = newPlaneButtonGroup;
        
    baseNode->addChild(RecruitButton::create(Size(getContentSize().width / 2, getContentSize().height / 10), _recruitContext));

    auto selectButton = SelectStageButton::create(Size(getContentSize().width / 2, getContentSize().height / 10), _recruitContext);
    selectButton->setPosition(Vec2(baseNode->getContentSize().width / 2, getContentSize().height / 10));
    baseNode->addChild(selectButton);
    
    return true;
}

void LobbyLayer::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void LobbyLayer::createBattleButton()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    auto battleButton = LaneListItem::create("Images/CyanSquare.png", "BATTLE");
    battleButton->addClickEventListener([](Ref* sender)
    {
        Director::getInstance()->pushScene(BattleLayer::scene(1, std::shared_ptr<RecruitContext>(new RecruitContext)));
    });
    battleButton->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
    battleButton->setPosition(origin + Vec2(visibleSize.width, 0));
    addChild(battleButton);
}

void LobbyLayer::setLaneButtonString(LaneId laneId, const std::string& text) const
{
    auto lli = dynamic_cast<LaneListItem*>(_laneButtonGroup->getChildren().at(laneId.GetValue()));
    lli->setString(text);
}

void LobbyLayer::updateResBar() const
{
    _resBar->updateGold();
}
