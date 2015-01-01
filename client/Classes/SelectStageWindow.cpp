#include "SelectStageWindow.h"
#include "Player.h"
#include "ResourceBar.h"
#include "AirplaneListItem.h"
#include "HelloWorldScene.h"
#include "BattleLayer.h"
#include "FontSize.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;

SelectStageWindow* SelectStageWindow::s_ins;

void SelectStageWindow::open(std::shared_ptr<RecruitContext> recruitContext)
{
    if (s_ins)
        return;

    Director::getInstance()->pushScene(SelectStageWindow::scene(recruitContext));
}

void SelectStageWindow::close()
{
    if (s_ins == nullptr)
        return;

    Director::getInstance()->popScene();
    s_ins = nullptr;
}

Scene* SelectStageWindow::scene(std::shared_ptr<RecruitContext> recruitContext)
{
    auto scene = Scene::create();
    
    auto layer = SelectStageWindow::create(recruitContext);

    layer->setName("SelectStageWindow");

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

SelectStageWindow* SelectStageWindow::create(std::shared_ptr<RecruitContext> recruitContext)
{
    auto ret = new (std::nothrow) SelectStageWindow();

    if (ret && ret->initWithSize(Director::getInstance()->getVisibleSize() * 0.8f))
    {
        ret->_recruitContext = recruitContext;
        ret->setPosition(Director::getInstance()->getVisibleOrigin() + Director::getInstance()->getVisibleSize() * 0.1f);
        ret->autorelease();

        s_ins = ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool SelectStageWindow::initWithSize(const Size& size)
{
    if (RelativeBox::initWithSize(size) == false)
        return false;

    auto vBox = createRootBox();
    vBox->addChild(createWinTitle("Select Stage"));
    vBox->addChild(createScrollView());
    vBox->addChild(createCloseButton("\nClose [X]\n "));
    addChild(vBox);

    vBox->getChildren().at(1)->setContentSize(getContentSize() - Size(0, vBox->getChildren().at(0)->getContentSize().height + vBox->getChildren().at(2)->getContentSize().height));

    return true;
}

Node* SelectStageWindow::createRootBox() const
{
    auto vBox = VBox::create();
    vBox->setContentSize(getContentSize());
    return vBox;
}

Node* SelectStageWindow::createWinTitle(const std::string& title) const
{
    auto button = Button::create("images/CyanSquareSmall.png");
    button->setTitleColor(Color3B::BLACK);
    button->setTitleFontSize(FontSize::getSmall());
    button->setTitleText(title);
    button->setScale9Enabled(true);
    button->setContentSize(Size(getContentSize().width, button->getTitleRenderer()->getContentSize().height));
    return button;
}

Node* SelectStageWindow::createScrollView()
{
    auto scrollView = ui::ScrollView::create();
    scrollView->setBackGroundColorType(BackGroundColorType::SOLID);
    scrollView->setBackGroundColor(Color3B::BLUE);
    scrollView->setBounceEnabled(true);
    scrollView->setDirection(ui::ScrollView::Direction::VERTICAL);
    //scrollView->setContentSize(Size(getContentSize().width, 2 * FontSize::getSmall()));

    auto scrollViewBox = createScrollViewBox();
    scrollView->addChild(scrollViewBox);

    scrollView->setInnerContainerSize(scrollViewBox->getContentSize());

    return scrollView;
}

Node* SelectStageWindow::createScrollViewBox()
{
    auto vBox = VBox::create();
    vBox->addChild(createCheatButton("\nAnyang\n ", [this]()
    {
        Player::gold = 0;
        ResourceBar::s_ins->updateGold();
        close();

        Director::getInstance()->pushScene(BattleLayer::scene(_recruitContext));
    }));
    vBox->addChild(createCheatButton("\nJamsil\n ", []()
    {
        Player::gold += 100;
        ResourceBar::s_ins->updateGold();
        close();
    }));
    vBox->addChild(createCheatButton("\nYoido\n ", []()
    {
        Player::gold += 200;
        ResourceBar::s_ins->updateGold();
        close();
    }));
    vBox->addChild(createCheatButton("\nStage 1\n ", []()
    {
        Player::gold += 300;
        ResourceBar::s_ins->updateGold();
        close();
    }));
    vBox->setContentSize(Size(getContentSize().width, sumContentSizeHeight(vBox)));
    return vBox;
}

cocos2d::Node* SelectStageWindow::createCheatButton(const std::string& title, std::function<void()> action)
{
    auto button = Button::create("images/YellowSquareSmall.png");
    button->setTitleColor(Color3B::BLACK);
    button->setTitleFontSize(FontSize::getVerySmall());
    button->setTitleText(title);
    button->setScale9Enabled(true);
    button->setContentSize(Size(getContentSize().width, button->getTitleRenderer()->getContentSize().height));
    button->addClickEventListener([action](Ref* sender)
    {
        action();
    });
    return button;
}

Node* SelectStageWindow::createCloseButton(const std::string& title)
{
    auto button = Button::create("images/MagentaSquareSmall.png");
    button->setTitleColor(Color3B::BLACK);
    button->setTitleFontSize(FontSize::getVerySmall());
    button->setTitleText(title);
    button->setScale9Enabled(true);
    button->setContentSize(Size(getContentSize().width, button->getTitleRenderer()->getContentSize().height));
    button->addClickEventListener([this](Ref* sender)
    {
        close();
    });
    return button;
}

float SelectStageWindow::sumContentSizeHeight(cocos2d::Node* node) const
{
    auto sum = 0.0f;
    for (auto c : node->getChildren())
    {
        sum += c->getContentSize().height;
    }
    return sum;
}
