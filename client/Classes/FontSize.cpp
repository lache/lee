#include "FontSize.h"
#include "cocos2d.h"
USING_NS_CC;

float FontSize::getSmall()
{
    const static auto v = Director::getInstance()->getOpenGLView()->getDesignResolutionSize().height / 35;
    return v;
}

float FontSize::getNormal()
{
    const static auto v = Director::getInstance()->getOpenGLView()->getDesignResolutionSize().height / 25;
    return v;
}

float FontSize::getLarge()
{
    const static auto v = Director::getInstance()->getOpenGLView()->getDesignResolutionSize().height / 15;
    return v;
}
