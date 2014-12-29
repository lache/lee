#ifndef __ResourceBar_H__
#define __ResourceBar_H__

#include "cocos2d.h"

class ResourceBar : public cocos2d::Node
{
public:
    static ResourceBar* create();

    void updateGold() const;

    virtual void onEnter() override;

CC_CONSTRUCTOR_ACCESS:
    virtual bool init();

private:

    void updateSize();

    cocos2d::Label* _label;
    cocos2d::Sprite* _background;
};

#endif // __ResourceBar_H__
