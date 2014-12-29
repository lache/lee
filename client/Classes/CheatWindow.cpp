#include "CheatWindow.h"
#include "Player.h"
#include "ResourceBar.h"
#include "AirplaneListItem.h"
#include "HelloWorldScene.h"
#include "FontSize.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;

CheatWindow* CheatWindow::s_ins;

void CheatWindow::open()
{
    if (s_ins)
        return;

    Director::getInstance()->getRunningScene()->addChild(create());
}

void CheatWindow::close()
{
    if (s_ins == nullptr)
        return;

    s_ins->removeFromParent();
    s_ins = nullptr;
}

CheatWindow* CheatWindow::create()
{
    auto ret = new (std::nothrow) CheatWindow();

    if (ret && ret->initWithSize(Director::getInstance()->getVisibleSize()))
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

bool CheatWindow::initWithSize(const Size& size)
{
    if (RelativeBox::initWithSize(size) == false)
        return false;

    auto vBox = createRootBox();
    vBox->addChild(createWinTitle("Cheat"));
    vBox->addChild(createScrollView());
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

Node* CheatWindow::createScrollView()
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

Node* CheatWindow::createScrollViewBox()
{
    auto vBox = VBox::create();
    vBox->addChild(createCheatButton("\nGold 0 (reset)\n ", []()
    {
        Player::gold = 0;
        ResourceBar::s_ins->updateGold();
        close();
    }));
    vBox->addChild(createCheatButton("\nGold +100\n ", []()
    {
        Player::gold += 100;
        ResourceBar::s_ins->updateGold();
        close();
    }));
    vBox->addChild(createCheatButton("\nGold +200\n ", []()
    {
        Player::gold += 200;
        ResourceBar::s_ins->updateGold();
        close();
    }));
    vBox->addChild(createCheatButton("\nGold +300\n ", []()
    {
        Player::gold += 300;
        ResourceBar::s_ins->updateGold();
        close();
    }));
    vBox->addChild(createCheatButton("\nGold +400\n ", []()
    {
        Player::gold += 400;
        ResourceBar::s_ins->updateGold();
        close();
    }));
    vBox->addChild(createCheatButton("\nGold +500\n ", []()
    {
        Player::gold += 500;
        ResourceBar::s_ins->updateGold();
        close();
    }));
    vBox->addChild(createCheatButton("\nGold +600\n ", []()
    {
        Player::gold += 600;
        ResourceBar::s_ins->updateGold();
        close();
    }));
    vBox->addChild(createCheatButton("\nGold +700\n ", []()
    {
        Player::gold += 700;
        ResourceBar::s_ins->updateGold();
        close();
    }));
    vBox->addChild(createCheatButton("\nGold +800\n ", []()
    {
        Player::gold += 800;
        ResourceBar::s_ins->updateGold();
        close();
    }));
    vBox->addChild(createCheatButton("\nGold +900\n ", []()
    {
        Player::gold += 900;
        ResourceBar::s_ins->updateGold();
        close();
    }));
    vBox->addChild(createCheatButton("\nGold +1000\n ", []()
    {
        Player::gold += 1000;
        ResourceBar::s_ins->updateGold();
        close();
    }));
    vBox->addChild(createCheatButton("\nGold +1100\n ", []()
    {
        Player::gold += 1100;
        ResourceBar::s_ins->updateGold();
        close();
    }));
    vBox->addChild(createCheatButton("\nGold +1200\n ", []()
    {
        Player::gold += 1200;
        ResourceBar::s_ins->updateGold();
        close();
    }));
    vBox->addChild(createCheatButton("\nGold +1300\n ", []()
    {
        Player::gold += 1300;
        ResourceBar::s_ins->updateGold();
        close();
    }));
    vBox->addChild(createCheatButton("\nGold +1400\n ", []()
    {
        Player::gold += 1400;
        ResourceBar::s_ins->updateGold();
        close();
    }));
    vBox->addChild(createCheatButton("\nGold +1500\n ", []()
    {
        Player::gold += 1500;
        ResourceBar::s_ins->updateGold();
        close();
    }));
    vBox->addChild(createCheatButton("\nGold +1600\n ", []()
    {
        Player::gold += 1600;
        ResourceBar::s_ins->updateGold();
        close();
    }));
    vBox->addChild(createCheatButton("\nGold +1700\n ", []()
    {
        Player::gold += 1700;
        ResourceBar::s_ins->updateGold();
        close();
    }));
    vBox->addChild(createCheatButton("\nGold +1800\n ", []()
    {
        Player::gold += 1800;
        ResourceBar::s_ins->updateGold();
        close();
    }));
    vBox->setContentSize(Size(getContentSize().width, sumContentSizeHeight(vBox)));
    return vBox;
}

cocos2d::Node* CheatWindow::createCheatButton(const std::string& title, std::function<void()> action)
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
