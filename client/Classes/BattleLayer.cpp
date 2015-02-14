#include "BattleLayer.h"
#include "LaneListItem.h"
#include "PlayerModel.h"
#include "BattleModel.h"
#include "BattleModel.h"
#include "Actor.h"
#include "Rand.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;

Scene* BattleLayer::scene(int stageId, const PlayerModelPtr& playerModel)
{
    auto scene = Scene::create();

    BattleLayer *layer = BattleLayer::create();

    layer->setName("BattleLayer");
    layer->initBattleContext(stageId, playerModel);

    scene->addChild(layer);

    return scene;
}

bool BattleLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    auto hBox = HBox::create();
    hBox->setPosition(origin + Vec2(0, visibleSize.height));
    addChild(hBox);

    auto goBackButton = Button::create("images/CyanSquare.png");
    goBackButton->setTitleText("GO BACK");
    goBackButton->addClickEventListener([](Ref* sender)
    {
        Director::getInstance()->popScene();
    });
    hBox->addChild(goBackButton);

    _battleground = Node::create();
    _battleground->setPosition(origin);
    addChild(_battleground);

    resetBattleground();

    return true;
}

void BattleLayer::initBattleContext(int stageId, const PlayerModelPtr& playerModel)
{   
    _stageId = stageId;

    for (auto& kv : playerModel->_battle->_fighter_map)
    {
        for (auto i = 0U; i < kv.second.size(); ++i)
        {
            spawnActor(1);
        }
    }
    
    for (auto i = 0U; i < playerModel->_battle->_enemy_map.size(); ++i)
    {
        spawnActor(2);
    }
    
    //_battleContext->setTeamSize(playerModel->getCurrentRecruitSize(), enemySize);
    //playerModel->clearRecruit();
}

void BattleLayer::resetBattleground()
{
    _battleground->removeAllChildren();
    Actor::cleanupActors();

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    /*auto actor = Actor::create(1);
    actor->setMoveSpeed(50);
    actor->setPosition(visibleSize / 2);
    _battleground->addChild(actor);

    auto actor2 = Actor::create(2);
    actor2->setMoveSpeed(0);
    actor2->setAttackPower(0);
    actor2->setPosition(visibleSize / 1.1f);
    _battleground->addChild(actor2);

    auto actor3 = Actor::create(2);
    actor3->setPosition(visibleSize / 4);
    _battleground->addChild(actor3);*/
}

void BattleLayer::spawnActor(int team)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();

    auto actor = Actor::create(team, _battleModel);
    actor->setHp(10 + Rand::get() * 10);
    actor->setMoveSpeed(50 + (-10 + Rand::get() * 20));
    const static float spawnRange = 200;
    actor->setPosition(Vec2(visibleSize) / 2 + Vec2(-spawnRange / 2 + Rand::get() * spawnRange, -spawnRange / 2 + Rand::get() * spawnRange));
    _battleground->addChild(actor);
}
