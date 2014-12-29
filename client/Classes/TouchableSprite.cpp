#include "TouchableSprite.h"

USING_NS_CC;

TouchableSprite* TouchableSprite::create(const std::string& filename, int priority)
{
	auto ret = new (std::nothrow) TouchableSprite(priority);
	
	if (ret && ret->initWithFile(filename))
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

void TouchableSprite::onEnter()
{
	Sprite::onEnter();

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = [=](Touch* touch, Event* event){

		Vec2 locationInNode = this->convertToNodeSpace(touch->getLocation());
		Size s = this->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);

		if (rect.containsPoint(locationInNode))
		{
			this->setColor(Color3B::RED);
			return true;
		}
		return false;
	};

	listener->onTouchEnded = [=](Touch* touch, Event* event){
		this->setColor(Color3B::WHITE);

		if (_removeListenerOnTouchEnded)
		{
			_eventDispatcher->removeEventListener(listener);
		}
	};

	if (_fixedPriority != 0)
	{
		_eventDispatcher->addEventListenerWithFixedPriority(listener, _fixedPriority);
	}
	else
	{
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	}

	_listener = listener;
}

void TouchableSprite::onExit()
{
	_eventDispatcher->removeEventListener(_listener);

	Sprite::onExit();
}
