#ifndef __CheatWindow_H__
#define __CheatWindow_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"

class CheatWindow : public cocos2d::ui::RelativeBox
{
public:
    static void open();
    static void close();
    static CheatWindow* create();

CC_CONSTRUCTOR_ACCESS:
    virtual bool initWithSize(const cocos2d::Size& size) override;

private:
    cocos2d::Node* createRootBox() const;
    cocos2d::Node* createWinTitle(const std::string& title) const;
    cocos2d::Node* createScrollView();
    cocos2d::Node* createScrollViewBox();
    cocos2d::Node* createCheatButton(const std::string& title, std::function<void()> action);
    cocos2d::Node* createCloseButton(const std::string& title);

    float sumContentSizeHeight(cocos2d::Node* node) const;

    static CheatWindow* s_ins;
};

#endif // __CheatWindow_H__
