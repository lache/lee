#ifndef __TOUCHABLESPRITE_H__
#define __TOUCHABLESPRITE_H__

#include "cocos2d.h"

class TouchableSprite : public cocos2d::Sprite
{
public:
	static TouchableSprite* create(const std::string& filename, int priority = 0);

protected:
	TouchableSprite(int priority)
		: _listener(nullptr)
		, _fixedPriority(priority)
		, _removeListenerOnTouchEnded(false)
	{
	}

public:
	void onEnter() override;

	void onExit() override;

	void removeListenerOnTouchEnded(bool toRemove) { _removeListenerOnTouchEnded = toRemove; };

	inline cocos2d::EventListener* getListener() { return _listener; };

private:
	cocos2d::EventListener* _listener;
	int _fixedPriority;
	bool _removeListenerOnTouchEnded;
};

#endif // __TOUCHABLESPRITE_H__
