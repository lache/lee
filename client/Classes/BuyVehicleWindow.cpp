#include "BuyVehicleWindow.h"
#include "Player.h"
#include "ResourceBar.h"

#include "SimplePopup.h"
#include "LobbyLayer.h"
#include "FontSize.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;

BuyVehicleWindow* BuyVehicleWindow::s_ins;

BuyVehicleWindow::BuyVehicleWindow()
    : _laneId(0)
{
}

BuyVehicleWindow::~BuyVehicleWindow()
{
}

void BuyVehicleWindow::open(int laneId)
{
    if (s_ins)
        return;

    Director::getInstance()->getRunningScene()->addChild(create(laneId));
}

void BuyVehicleWindow::close()
{
    if (s_ins == nullptr)
        return;

    s_ins->removeFromParent();
    s_ins = nullptr;
}

BuyVehicleWindow* BuyVehicleWindow::create(int laneId)
{
    auto ret = new (std::nothrow) BuyVehicleWindow();

    const auto marginWidth = 50;
    const auto marginHeight = 50;

    if (ret && ret->initWithLaneId(Director::getInstance()->getVisibleSize() - Size(marginWidth * 2, marginHeight * 2), laneId))
    {
        ret->setPosition(Director::getInstance()->getVisibleOrigin() + Vec2(marginWidth, marginHeight));
        ret->autorelease();

        s_ins = ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool BuyVehicleWindow::initWithLaneId(const Size& size, int laneId)
{
    if (RelativeBox::initWithSize(size) == false)
        return false;

    _laneId = laneId;

    auto vBox = createRootBox();
    vBox->addChild(createWinTitle("New Vehicle"));
    vBox->addChild(createScrollView());
    vBox->addChild(createCloseButton("\nClose [X]\n "));
    addChild(vBox);

    vBox->getChildren().at(1)->setContentSize(getContentSize() - Size(0, vBox->getChildren().at(0)->getContentSize().height + vBox->getChildren().at(2)->getContentSize().height));

    return true;
}

Node* BuyVehicleWindow::createRootBox() const
{
    auto vBox = VBox::create();
    vBox->setContentSize(getContentSize());
    return vBox;
}

Node* BuyVehicleWindow::createWinTitle(const std::string& title) const
{
    auto button = Button::create("images/CyanSquareSmall.png");
    button->setTitleColor(Color3B::BLACK);
    button->setTitleFontSize(FontSize::getSmall());
    button->setTitleText(title);
    button->setScale9Enabled(true);
    button->setContentSize(Size(getContentSize().width, button->getTitleRenderer()->getContentSize().height));
    return button;
}

Node* BuyVehicleWindow::createScrollView()
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

Node* BuyVehicleWindow::createScrollViewBox()
{
    auto vBox = VBox::create();
    vBox->addChild(createVehicleButton(1));
    vBox->addChild(createVehicleButton(2));
    vBox->addChild(createVehicleButton(3));
    vBox->setContentSize(Size(getContentSize().width, sumContentSizeHeight(vBox)));
    return vBox;
}

int CalculatePriceFromVehicleId(int vehicleId)
{
    return vehicleId * 100;
}

cocos2d::Node* BuyVehicleWindow::createVehicleButton(int vehicleId)
{
    auto button = Button::create("images/YellowSquareSmall.png");
    button->setTitleColor(Color3B::BLACK);
    button->setTitleFontSize(FontSize::getVerySmall());
    button->setTitleText(StringUtils::format("\nVehicle ID %d - Gold %d\n ", vehicleId, CalculatePriceFromVehicleId(vehicleId)));
    button->setScale9Enabled(true);
    button->setContentSize(Size(getContentSize().width, button->getTitleRenderer()->getContentSize().height));
    button->addClickEventListener([button, vehicleId](Ref* sender)
    {
        CCLOG("Vehicle ID %d clicked, position = (%f, %f)", vehicleId, button->getPosition().x, button->getPosition().y);

        auto director = Director::getInstance();
        auto root = director->getRunningScene()->getChildByName<LobbyLayer*>("LobbyLayer");

        auto price = CalculatePriceFromVehicleId(vehicleId);
        if (Player::gold < price)
        {
            auto popup = SimplePopup::create("** Insufficient funds **", Color4B::RED);
            popup->runAction(Sequence::create(DelayTime::create(1), FadeOut::create(0.3f), RemoveSelf::create(), nullptr));

            root->addChild(popup);
        }
        else
        {
            Player::gold -= price;

            auto buttonText = StringUtils::format("V %d", vehicleId);
            root->setLaneButtonString(BuyVehicleWindow::s_ins->getLane(), buttonText);

            root->updateResBar();

            BuyVehicleWindow::close();
        }
    });
    return button;
}

Node* BuyVehicleWindow::createCloseButton(const std::string& title)
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

float BuyVehicleWindow::sumContentSizeHeight(cocos2d::Node* node) const
{
    auto sum = 0.0f;
    for (auto c : node->getChildren())
    {
        sum += c->getContentSize().height;
    }
    return sum;
}
