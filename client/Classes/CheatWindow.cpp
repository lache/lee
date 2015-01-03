#include "CheatWindow.h"
#include "Player.h"
#include "ResourceBar.h"
#include "PlayerModel.h"
#include "FontSize.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;

CheatWindow* CheatWindow::s_ins;

void CheatWindow::open(const PlayerModelPtr& playerModel)
{
    if (s_ins)
        return;

    Director::getInstance()->getRunningScene()->addChild(create(playerModel));
}

void CheatWindow::close()
{
    if (s_ins == nullptr)
        return;

    s_ins->removeFromParent();
    s_ins = nullptr;
}

CheatWindow* CheatWindow::create(const PlayerModelPtr& playerModel)
{
    auto ret = new (std::nothrow) CheatWindow();

    if (ret && ret->initWithPlayer(Director::getInstance()->getVisibleSize(), playerModel))
    {
        ret->setPosition(Director::getInstance()->getVisibleOrigin());
        ret->autorelease();

        s_ins = ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool CheatWindow::initWithPlayer(const Size& size, const PlayerModelPtr& playerModel)
{
    if (RelativeBox::initWithSize(size) == false)
        return false;

    auto vBox = createRootBox();
    vBox->addChild(createWinTitle("Cheat"));
    vBox->addChild(createScrollView(playerModel));
    vBox->addChild(createCloseButton("\nClose [X]\n "));
    addChild(vBox);

    vBox->getChildren().at(1)->setContentSize(getContentSize() - Size(0, vBox->getChildren().at(0)->getContentSize().height + vBox->getChildren().at(2)->getContentSize().height));

    return true;
}

Node* CheatWindow::createRootBox() const
{
    auto vBox = VBox::create();
    vBox->setContentSize(getContentSize());
    return vBox;
}

Node* CheatWindow::createWinTitle(const std::string& title) const
{
    auto button = Button::create("images/CyanSquareSmall.png");
    button->setTitleColor(Color3B::BLACK);
    button->setTitleFontSize(FontSize::getSmall());
    button->setTitleText(title);
    button->setScale9Enabled(true);
    button->setContentSize(Size(getContentSize().width, button->getTitleRenderer()->getContentSize().height));
    return button;
}

Node* CheatWindow::createScrollView(const PlayerModelPtr& playerModel)
{
    auto scrollView = ui::ScrollView::create();
    scrollView->setBackGroundColorType(BackGroundColorType::SOLID);
    scrollView->setBackGroundColor(Color3B::BLUE);
    scrollView->setBounceEnabled(true);
    scrollView->setDirection(ui::ScrollView::Direction::VERTICAL);
    //scrollView->setContentSize(Size(getContentSize().width, 2 * FontSize::getSmall()));

    auto scrollViewBox = createScrollViewBox(playerModel);
    scrollView->addChild(scrollViewBox);

    scrollView->setInnerContainerSize(scrollViewBox->getContentSize());

    return scrollView;
}

Node* CheatWindow::createScrollViewBox(const PlayerModelPtr& playerModel)
{
    auto vBox = VBox::create();
    vBox->addChild(createCheatButton("\nGold +1000\n ", playerModel));
    vBox->setContentSize(Size(getContentSize().width, sumContentSizeHeight(vBox)));
    return vBox;
}

cocos2d::Node* CheatWindow::createCheatButton(const std::string& title, const PlayerModelPtr& playerModel)
{
    auto button = Button::create("images/YellowSquareSmall.png");
    button->setTitleColor(Color3B::BLACK);
    button->setTitleFontSize(FontSize::getVerySmall());
    button->setTitleText(title);
    button->setScale9Enabled(true);
    button->setContentSize(Size(getContentSize().width, button->getTitleRenderer()->getContentSize().height));
    button->addClickEventListener([playerModel](Ref* sender)
    {
        playerModel->_gold += 1000;
        ResourceBar::s_ins->updateGold();
        close();
    });
    return button;
}

Node* CheatWindow::createCloseButton(const std::string& title)
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

float CheatWindow::sumContentSizeHeight(cocos2d::Node* node) const
{
    auto sum = 0.0f;
    for (auto c : node->getChildren())
    {
        sum += c->getContentSize().height;
    }
    return sum;
}
