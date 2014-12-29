#include "HelloWorldScene.h"
#include "TouchableSprite.h"
#include "BuyAirplaneWindow.h"
#include "LaneListItem.h"
#include "ResourceBar.h"
#include "PopText.h"
#include "BattleLayer.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"
#include <random>
USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;


Scene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

	layer->setName("HelloWorldLayer");

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    
    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    //auto label = LabelTTF::create("Hello World", "Arial", TITLE_FONT_SIZE);
    //
    //// position the label on the center of the screen
    //label->setPosition(origin.x + visibleSize.width/2,
    //                        origin.y + visibleSize.height - label->getContentSize().height);

    // add the label as a child to this layer
    //this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("title2.png");
	sprite->setAnchorPoint(Vec2(0.5f, 1.0f));
	sprite->setScale(visibleSize.height / sprite->getContentSize().height);
    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height) + origin);



    // add the sprite as a child to this layer
	this->addChild(sprite);

/*
	{
		auto hbox = HBox::create();
		hbox->setPosition(origin + Vec2(0, visibleSize.height / 2));
		addChild(hbox);

		auto sprite1 = ImageView::create("Images/CyanSquare.png");
		hbox->addChild(sprite1, 10);

		auto sprite2 = ImageView::create("Images/YellowSquare.png");
		hbox->addChild(sprite2, 10);

		auto sprite3 = ImageView::create("Images/YellowSquare.png");
		hbox->addChild(sprite3, 10);
	}*/
	
	auto newPlaneButtonGroup = Node::create();
	newPlaneButtonGroup->setPosition(origin + Vec2(0, visibleSize.height / 3));
	newPlaneButtonGroup->setContentSize(Size(visibleSize.width, visibleSize.height / 6));
	addChild(newPlaneButtonGroup);

	for (int i = 0; i < 4; ++i)
	{
		auto sprite = LaneListItem::create("Images/CyanSquare.png", "E");// TouchableSprite::create("Images/CyanSquare.png", 40 - i * 10);
		sprite->addClickEventListener([&, i](Ref* sender)
		{
			//CCLOG(("Click " + std::to_string(i)).c_str());

			if (_buyAirplaneWindow->getParent() != nullptr)
			{
				_buyAirplaneWindow->removeFromParent();
			}
			else
			{
				addChild(_buyAirplaneWindow);
				_buyAirplaneWindow->setLane(i);
			}
		});
		sprite->setAnchorPoint(Vec2::ZERO);
		sprite->setScaleX(newPlaneButtonGroup->getContentSize().width / sprite->getContentSize().width / 4);
		sprite->setScaleY(newPlaneButtonGroup->getContentSize().height / sprite->getContentSize().height);
		sprite->setPosition(Vec2(newPlaneButtonGroup->getContentSize().width / 4 * i, 0));
		newPlaneButtonGroup->addChild(sprite);
	}

	_laneButtonGroup = newPlaneButtonGroup;

	auto buyAirplaneWindow = BuyAirplaneWindow::create();
	buyAirplaneWindow->setPosition(origin + visibleSize / 2);
	buyAirplaneWindow->retain();
	_buyAirplaneWindow = buyAirplaneWindow;

	auto resBar = ResourceBar::create();
	resBar->setContentSize(Size(visibleSize.width, 10));
	resBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
	resBar->setNormalizedPosition(Vec2::ANCHOR_MIDDLE_TOP);
	addChild(resBar);
	_resBar = resBar;
	updateResBar();


	std::mt19937 generator;

	generator.seed(1985);

	std::uniform_real_distribution<float> distribution(0, static_cast<float>(2 * M_PI));
	auto twoPi = std::bind(distribution, generator);

	std::mt19937 generator2;
	generator2.seed(1981);
	std::uniform_real_distribution<float> zeroOneDistribution(0, 1);
	auto zeroOne = std::bind(zeroOneDistribution, generator2);

	for (int i = 0; i < 100; ++i)
	{
		auto theta = twoPi();
		auto delay = zeroOne() * 5;

		auto rat = theta / delay;

		auto fighter01 = Sprite::create();
		//fighter01->setPosition(origin + visibleSize / 2 + 350 * Vec2(cosf(r * 2 * M_PI), sinf(r * 2 * M_PI)));
		fighter01->setPosition(origin + visibleSize / 2 + 350 * Vec2(cosf(theta), sinf(theta)));
		fighter01->runAction(RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("fighter01"))));
		fighter01->runAction(Sequence::create(
			DelayTime::create(delay),
			MoveTo::create(1, origin + visibleSize / 2),
			DelayTime::create(0.2f),
			CallFunc::create([=]() { PopText::create(this, fighter01->getPosition(), "+1"); }),
			RemoveSelf::create(),
			nullptr));
		addChild(fighter01);
	}

	createBattleButton();
	
    return true;
}

void HelloWorld::createBattleButton()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	auto battleButton = LaneListItem::create("Images/CyanSquare.png", "BATTLE");
	battleButton->addClickEventListener([](Ref* sender)
	{
		Director::getInstance()->pushScene(BattleLayer::scene());
	});
	battleButton->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	battleButton->setPosition(origin + Vec2(visibleSize.width, 0));
	addChild(battleButton);
}

void HelloWorld::menuCloseCallback(Ref* sender)
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

void HelloWorld::setLaneButtonString(int laneId, const std::string& text) const
{
	auto lli = dynamic_cast<LaneListItem*>(_laneButtonGroup->getChildren().at(laneId));
	lli->setString(text);
}

void HelloWorld::updateResBar() const
{
	_resBar->updateGold();
}
