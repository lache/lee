#include "SelectStageWindow.h"
#include "ResourceBar.h"
#include "BattleLayer.h"
#include "FontSize.h"
#include "playerModel.h"
#include "RecruitController.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;

SelectStageWindow* SelectStageWindow::s_ins;

void SelectStageWindow::open(const PlayerModelPtr& playerModel)
{
    if (s_ins)
        return;

    Director::getInstance()->pushScene(SelectStageWindow::scene(playerModel));
}

void SelectStageWindow::close()
{
    if (s_ins == nullptr)
        return;

    Director::getInstance()->popScene();
    s_ins = nullptr;
}

Scene* SelectStageWindow::scene(const PlayerModelPtr& playerModel)
{
    auto scene = Scene::create();
    
    auto layer = SelectStageWindow::create(playerModel);

    layer->setName("SelectStageWindow");

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

SelectStageWindow* SelectStageWindow::create(const PlayerModelPtr& playerModel)
{
    auto ret = new (std::nothrow) SelectStageWindow();

    if (ret && ret->initWithSize(Director::getInstance()->getVisibleSize() * 0.8f))
    {
        ret->_playerModel = playerModel;
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

void SelectStageWindow::startBattle(int stageId)
{
    close();

    RecruitController::StopRecruit(_playerModel);

    Director::getInstance()->pushScene(BattleLayer::scene(stageId, _playerModel));
}

Node* SelectStageWindow::createScrollViewBox()
{
    auto vBox = VBox::create();
    vBox->addChild(createCheatButton("\nAnyang\n ", [this]() { startBattle(1); }));
    vBox->addChild(createCheatButton("\nJamsil\n ", [this]() { startBattle(2); }));
    vBox->addChild(createCheatButton("\nYoido\n ", [this]() { startBattle(3); }));
    vBox->addChild(createCheatButton("\nBeijing\n ", [this]() { startBattle(4); }));
    vBox->addChild(createCheatButton("\nCalifornia\n ", [this]() { startBattle(5); }));
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
