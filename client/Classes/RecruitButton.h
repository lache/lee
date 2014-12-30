#ifndef __RecruitButton_H__
#define __RecruitButton_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class RecruitContext;

class RecruitButton : public cocos2d::ui::Button
{
public:
    static RecruitButton* create(const cocos2d::Size& size, std::shared_ptr<RecruitContext> recruitContext);

    enum class ButtonState : std::int8_t
    {
        CAN_RECRUIT,
        RECRUIT_IN_PROGRESS,
    };

    void setButtonState(ButtonState state, int currentRecruitSize = 0);

CC_CONSTRUCTOR_ACCESS:
    virtual bool init(const cocos2d::Size& size, std::shared_ptr<RecruitContext> recruitContext);

private:
    RecruitButton();

    void startBlinkAction();

    int _currentRecruitSize;
};

#endif // __RecruitButton_H__
