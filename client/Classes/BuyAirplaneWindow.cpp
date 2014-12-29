#include "BuyAirplaneWindow.h"
#include "Player.h"
#include "ResourceBar.h"
#include "AirplaneListItem.h"
#include "HelloWorldScene.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;

BuyAirplaneWindow* BuyAirplaneWindow::s_ins;

BuyAirplaneWindow* BuyAirplaneWindow::create(const Size& size)
{
    auto ret = new (std::nothrow) BuyAirplaneWindow();

    if (ret && ret->initWithSize(size))
    {
        ret->autorelease();

        BuyAirplaneWindow::s_ins = ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool BuyAirplaneWindow::initWithSize(const Size& size)
{
    if (RelativeBox::initWithSize(size) == false)
        return false;

    RelativeLayoutParameter* param = RelativeLayoutParameter::create();
    param->setAlign(RelativeAlign::CENTER_IN_PARENT);
    
    /*auto testButton = ui::Button::create("images/YellowSquare.png");
    addChild(testButton);
    testButton->setLayoutParameter(param);*/

    auto scrollView = ui::ScrollView::create();
    auto itemCount = 20;

    auto vBox = VBox::create();
    vBox->setLayoutParameter(param);
    scrollView->addChild(vBox);
    _vBox = vBox;
    for (int i = 0; i < itemCount; ++i)
    {
        auto buttonText = StringUtils::format("Airplane %d\nPrice 123456789\nthird\n4th", i);
        auto ali = AirplaneListItem::create("images/YellowSquare.png", buttonText, i);
        vBox->addChild(ali);
    }
    scrollView->setBackGroundColorType(BackGroundColorType::SOLID);
    scrollView->setBackGroundColor(Color3B::BLUE);
    scrollView->setBounceEnabled(true);
    scrollView->setDirection(ui::ScrollView::Direction::VERTICAL);
    //scrollView->setAnchorPoint(Vec2::ZERO);
    
    scrollView->setLayoutParameter(param);
    _scrollView = scrollView;

    auto closeButton = ui::Button::create("images/YellowSquare.png");
    closeButton->setTitleColor(Color3B::BLACK);
    closeButton->setTitleText("Close [X]");
    closeButton->setScale9Enabled(true);
    closeButton->setContentSize(Size(getContentSize().width, closeButton->getContentSize().height));
    closeButton->addClickEventListener([this](Ref* sender)
    {
        setVisible(false);
    });
    /*auto closeButtonLayoutParameter = LinearLayoutParameter::create();
    closeButtonLayoutParameter->setGravity(LinearGravity::CENTER_HORIZONTAL);
    closeButton->setLayoutParameter(closeButtonLayoutParameter);*/

    auto vBoxWindow = VBox::create();
    auto titleButton = ui::Button::create("images/CyanSquare.png");
    titleButton->setTitleColor(Color3B::BLACK);
    titleButton->setTitleText("Select New Vehicle");
    titleButton->setContentSize(Size(getContentSize().width, titleButton->getContentSize().height));
    titleButton->setScale9Enabled(true);
    //titleButton->setContentSize(Size(20, 20));
    vBoxWindow->addChild(titleButton);
    vBoxWindow->addChild(_scrollView);
    vBoxWindow->addChild(closeButton);
    //vBoxWindow->setLayoutParameter(param);
    addChild(vBoxWindow);

    /*auto sprite = Sprite::create("images/title.png");
    sprite->setAnchorPoint(Vec2::ZERO);
    sprite->setPosition(Vec2::ZERO);
    addChild(sprite);*/

    //setLayoutParameter(param);

    return true;
}

void BuyAirplaneWindow::onEnter()
{
    auto width = getContentSize().width;

    _vBox->setContentSize(Size(width, _vBox->getContentSize().height));

    RelativeBox::onEnter();

    auto scrollViewTotalHeight = 0.0f;
    for (auto v : _vBox->getChildren())
    {
        scrollViewTotalHeight += v->getContentSize().height;
    }

    _vBox->setContentSize(Size(width, scrollViewTotalHeight));
    _scrollView->setInnerContainerSize(Size(width, scrollViewTotalHeight));
    _scrollView->setContentSize(Size(width, getContentSize().height / 2));

    /*RelativeLayoutParameter* param = RelativeLayoutParameter::create();
    param->setAlign(RelativeAlign::CENTER_IN_PARENT);
    _scrollView->setLayoutParameter(param);*/

    

}
