#ifndef __ResourceBar_H__
#define __ResourceBar_H__

#include "cocos2d.h"
#include "cocos-ext.h"

class ResourceBar : public cocos2d::ui::Button
{
public:
    static ResourceBar* create();

    void updateGold();

    static ResourceBar* s_ins;

CC_CONSTRUCTOR_ACCESS:
    virtual bool init() override;
};

#endif // __ResourceBar_H__
