#ifndef __BattleResultWindow_H__
#define __BattleResultWindow_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"

class BattleResultWindow : public cocos2d::ui::RelativeBox
{
public:
    static void open(bool win, int score);
    static void close();
    
CC_CONSTRUCTOR_ACCESS:
    virtual bool initWithData(const cocos2d::Size& size, bool win, int score);

private:
    static BattleResultWindow* create(bool win, int score);
    
    cocos2d::Node* createRootBox() const;
    cocos2d::Node* createWinTitle(const std::string& title) const;
    cocos2d::Node* createScrollView(int score);
    cocos2d::Node* createScrollViewBox(int score);
    cocos2d::Node* createCheatButton(const std::string& title, std::function<void()> action);
    cocos2d::Node* createCloseButton(const std::string& title, int score);

    float sumContentSizeHeight(cocos2d::Node* node) const;

    static BattleResultWindow* s_ins;
};

#endif // __BattleResultWindow_H__
