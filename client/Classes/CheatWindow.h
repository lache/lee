#ifndef __CheatWindow_H__
#define __CheatWindow_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"
#include "Typedefs.h"

class CheatWindow : public cocos2d::ui::RelativeBox
{
public:
    static void open(const PlayerModelPtr& playerModel);
    static void close();
    static CheatWindow* create(const PlayerModelPtr& playerModel);

CC_CONSTRUCTOR_ACCESS:
    virtual bool initWithPlayer(const cocos2d::Size& size, const PlayerModelPtr& playerModel);

private:
    cocos2d::Node* createRootBox() const;
    cocos2d::Node* createWinTitle(const std::string& title) const;
    cocos2d::Node* createScrollView(const PlayerModelPtr& playerModel);
    cocos2d::Node* createScrollViewBox(const PlayerModelPtr& playerModel);
    cocos2d::Node* createCheatButton(const std::string& title, const PlayerModelPtr& playerModel);
    cocos2d::Node* createCloseButton(const std::string& title);

    float sumContentSizeHeight(cocos2d::Node* node) const;

    static CheatWindow* s_ins;
};

#endif // __CheatWindow_H__
