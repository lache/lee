#include "BattleLayer.h"
#include "LaneListItem.h"
#include "RecruitContext.h"
#include "BattleContext.h"
#include "Actor.h"
#include "Rand.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;


Scene* BattleLayer::scene(int stageId, const std::shared_ptr<RecruitContext>& recruitContext)
{
    auto scene = Scene::create();

    BattleLayer *layer = BattleLayer::create();

    layer->setName("BattleLayer");
    layer->initBattleContext(stageId, recruitContext);

    scene->addChild(layer);

    // return the scene
    return scene;
}

bool BattleLayer::init()
{
    //////////////////////////////
    // 1. super init first
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

    /*auto resetButton = Button::create("images/CyanSquare.png");
    resetButton->setTitleText("RESET");
    resetButton->addClickEventListener([this](Ref* sender)
    {
        resetBattleground();
    });
    hBox->addChild(resetButton);

    auto spawnTeam1 = Button::create("images/CyanSquare.png");
    spawnTeam1->setTitleText("SPAWN TEAM 1");
    spawnTeam1->addClickEventListener([this](Ref* sender)
    {
        spawnActor(1);
    });
    hBox->addChild(spawnTeam1);

    auto spawnTeam2 = Button::create("images/CyanSquare.png");
    spawnTeam2->setTitleText("SPAWN TEAM 2");
    spawnTeam2->addClickEventListener([this](Ref* sender)
    {
        spawnActor(2);
    });
    hBox->addChild(spawnTeam2);*/

    _battleground = Node::create();
    _battleground->setPosition(origin);
    addChild(_battleground);

    resetBattleground();

    return true;
}

void BattleLayer::initBattleContext(int stageId, const std::shared_ptr<RecruitContext>& recruitContext)
{   
    _stageId = stageId;

    _battleContext.reset(new BattleContext);

    for (auto i = 0; i < recruitContext->getCurrentRecruitSize(); ++i)
        spawnActor(1);

    auto enemySize = 5 * stageId;
    for (auto i = 0; i < enemySize; ++i)
        spawnActor(2);

    _battleContext->setTeamSize(recruitContext->getCurrentRecruitSize(), enemySize);

    recruitContext->clearRecruit();
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

    auto actor = Actor::create(team, _battleContext);
    actor->setHp(10 + Rand::get() * 10);
    actor->setMoveSpeed(50 + (-10 + Rand::get() * 20));
    const static float spawnRange = 200;
    actor->setPosition(Vec2(visibleSize) / 2 + Vec2(-spawnRange / 2 + Rand::get() * spawnRange, -spawnRange / 2 + Rand::get() * spawnRange));
    _battleground->addChild(actor);
}
