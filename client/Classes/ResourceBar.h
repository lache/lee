#ifndef __ResourceBar_H__
#define __ResourceBar_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Typedefs.h"

class ResourceBar : public cocos2d::ui::Button
{
public:
    static ResourceBar* create(const PlayerModelPtr& playerModel);

    void updateGold();

    static ResourceBar* s_ins;

CC_CONSTRUCTOR_ACCESS:
    virtual bool initWithPlayer(const PlayerModelPtr& playerModel);

    PlayerModelPtr _playerModel;
};

#endif // __ResourceBar_H__
