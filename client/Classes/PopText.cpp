#include "PopText.h"
USING_NS_CC;

void PopText::create(Node* parent, const Vec2& position, const std::string text)
{
    const static auto moveHeight = Director::getInstance()->getOpenGLView()->getDesignResolutionSize().height / 20;
    const static auto fontSize = Director::getInstance()->getOpenGLView()->getDesignResolutionSize().height / 20;

	auto label = Label::createWithSystemFont(text, "Arial", fontSize, Size::ZERO, cocos2d::TextHAlignment::CENTER, cocos2d::TextVAlignment::CENTER);
	label->setPosition(position);
	label->runAction(Sequence::create(MoveBy::create(0.5f, Vec2(0, moveHeight)), nullptr));
	label->runAction(Sequence::create(FadeOut::create(0.5f), RemoveSelf::create(), nullptr));
	parent->addChild(label);
}
