#include "BattleResultWindow.h"
#include "ResourceBar.h"
#include "LobbyLayer.h"
#include "FontSize.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;

BattleResultWindow* BattleResultWindow::s_ins;

void BattleResultWindow::open(bool win, int score)
{
    if (s_ins)
        return;

    Director::getInstance()->getRunningScene()->addChild(create(win, score));
}

void BattleResultWindow::close()
{
    if (s_ins == nullptr)
        return;

    s_ins->removeFromParent();
    s_ins = nullptr;

    Director::getInstance()->popScene();
}

BattleResultWindow* BattleResultWindow::create(bool win, int score)
{
    auto ret = new (std::nothrow) BattleResultWindow();

    if (ret && ret->initWithData(Size(Director::getInstance()->getVisibleSize().width * 0.9f, Director::getInstance()->getVisibleSize().height / 3), win, score))
    {
        ret->setPosition(Vec2(Director::getInstance()->getVisibleOrigin().x + Director::getInstance()->getVisibleSize().width / 2 - Director::getInstance()->getVisibleSize().width * 0.9f / 2, Director::getInstance()->getVisibleOrigin().y + Director::getInstance()->getVisibleSize().height / 2 - Director::getInstance()->getVisibleSize().height / 3 / 2));
        ret->autorelease();

        s_ins = ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool BattleResultWindow::initWithData(const Size& size, bool win, int score)
{
    if (RelativeBox::initWithSize(size) == false)
        return false;

    auto vBox = createRootBox();
    vBox->addChild(createWinTitle(win ? "WIN" : "LOSE"));
    vBox->addChild(createScrollView(score));
    vBox->addChild(createCloseButton("\nClose [X]\n ", score));
    addChild(vBox);

    vBox->getChildren().at(1)->setContentSize(getContentSize() - Size(0, vBox->getChildren().at(0)->getContentSize().height + vBox->getChildren().at(2)->getContentSize().height));

    return true;
}

Node* BattleResultWindow::createRootBox() const
{
    auto vBox = VBox::create();
    vBox->setContentSize(getContentSize());
    return vBox;
}

Node* BattleResultWindow::createWinTitle(const std::string& title) const
{
    auto button = Button::create("images/CyanSquareSmall.png");
    button->setTitleColor(Color3B::BLACK);
    button->setTitleFontSize(FontSize::getLarge());
    button->setTitleText(title);
    button->setScale9Enabled(true);
    button->setContentSize(Size(getContentSize().width, button->getTitleRenderer()->getContentSize().height));
    return button;
}

Node* BattleResultWindow::createScrollView(int score)
{
    auto scrollView = ui::ScrollView::create();
    scrollView->setBackGroundColorType(BackGroundColorType::SOLID);
    scrollView->setBackGroundColor(Color3B::BLUE);
    scrollView->setBounceEnabled(true);
    scrollView->setDirection(ui::ScrollView::Direction::VERTICAL);
    //scrollView->setContentSize(Size(getContentSize().width, 2 * FontSize::getSmall()));

    auto scrollViewBox = createScrollViewBox(score);
    scrollView->addChild(scrollViewBox);

    scrollView->setInnerContainerSize(scrollViewBox->getContentSize());

    return scrollView;
}

int CalculateGoldFromScore(int score)
{
    return score;
}

Node* BattleResultWindow::createScrollViewBox(int score)
{
    auto gold = CalculateGoldFromScore(score);

    auto vBox = VBox::create();
    vBox->addChild(createCheatButton(StringUtils::format("\nReward: Gold %d\n ", gold), [=]()
    {
        /*Player::gold += gold;
        ResourceBar::s_ins->updateGold();
        close();*/
    }));
    vBox->setContentSize(Size(getContentSize().width, sumContentSizeHeight(vBox)));
    return vBox;
}

cocos2d::Node* BattleResultWindow::createCheatButton(const std::string& title, std::function<void()> action)
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

Node* BattleResultWindow::createCloseButton(const std::string& title, int score)
{
    auto button = Button::create("images/MagentaSquareSmall.png");
    button->setTitleColor(Color3B::BLACK);
    button->setTitleFontSize(FontSize::getVerySmall());
    button->setTitleText(title);
    button->setScale9Enabled(true);
    button->setContentSize(Size(getContentSize().width, button->getTitleRenderer()->getContentSize().height));
    button->addClickEventListener([this, score](Ref* sender)
    {
        auto gold = CalculateGoldFromScore(score);

        //Player::gold += gold;
        ResourceBar::s_ins->updateGold();
        close();
    });
    return button;
}

float BattleResultWindow::sumContentSizeHeight(cocos2d::Node* node) const
{
    auto sum = 0.0f;
    for (auto c : node->getChildren())
    {
        sum += c->getContentSize().height;
    }
    return sum;
}
