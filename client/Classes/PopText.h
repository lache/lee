#ifndef __PopText_H__
#define __PopText_H__

#include "cocos2d.h"

class PopText
{
public:
	static void create(cocos2d::Node* parent, const cocos2d::Vec2& position, const std::string text);
};

#endif // __PopText_H__
