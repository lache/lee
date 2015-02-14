#ifndef __RecruitButton_H__
#define __RecruitButton_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Typedefs.h"

class RecruitButton : public cocos2d::ui::Button
{
public:
    static RecruitButton* create(const cocos2d::Size& size, const PlayerModelPtr& playerModel);

    enum class ButtonState : std::int8_t
    {
        CAN_RECRUIT,
        RECRUIT_IN_PROGRESS,
    };

    void setButtonState(ButtonState state, int currentRecruitSize = 0);

CC_CONSTRUCTOR_ACCESS:
    virtual bool init(const cocos2d::Size& size, const PlayerModelPtr& playerModel);

private:
    RecruitButton();

    void startBlinkAction();

    int _currentRecruitSize;
};

#endif // __RecruitButton_H__
