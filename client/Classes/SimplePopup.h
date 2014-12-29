#ifndef __SimplePopup_H__
#define __SimplePopup_H__

#include "cocos2d.h"

class SimplePopup : public cocos2d::LayerColor
{
public:
	static SimplePopup* create(const std::string& text, const cocos2d::Color4B& bgColor);

	virtual void onEnter() override;


CC_CONSTRUCTOR_ACCESS:
	virtual bool init(const std::string& text, const cocos2d::Color4B& bgColor);

private:
	cocos2d::Label* _label;
};

#endif // __SimplePopup_H__
