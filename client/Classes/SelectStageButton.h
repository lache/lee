#ifndef __SelectStageButton_H__
#define __SelectStageButton_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Typedefs.h"

class SelectStageButton : public cocos2d::ui::Button
{
public:
    static SelectStageButton* create(const cocos2d::Size& size, const PlayerModelPtr& playerModel);

    enum class ButtonState : std::int8_t
    {
        CANNOT_SELECT_STAGE, 
        CAN_SELECT_STAGE,
    };

    void setButtonState(ButtonState state, int currentRecruitSize = 0);

CC_CONSTRUCTOR_ACCESS:
    virtual bool init(const cocos2d::Size& size, const PlayerModelPtr& playerModel);

private:
    SelectStageButton();

    void startBlinkAction();
};

#endif // __SelectStageButton_H__
