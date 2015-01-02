#ifndef __SelectStageWindow_H__
#define __SelectStageWindow_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"

class RecruitContext;

class SelectStageWindow : public cocos2d::ui::RelativeBox
{
public:
    static void open(const std::shared_ptr<RecruitContext>& recruitContext);
    static void close();

CC_CONSTRUCTOR_ACCESS:
    virtual bool initWithSize(const cocos2d::Size& size) override;

private:
    static SelectStageWindow* create(const std::shared_ptr<RecruitContext>& recruitContext);
    static cocos2d::Scene* scene(const std::shared_ptr<RecruitContext>& recruitContext);
    void startBattle(int stageId);
    cocos2d::Node* createRootBox() const;
    cocos2d::Node* createWinTitle(const std::string& title) const;
    cocos2d::Node* createScrollView();
    cocos2d::Node* createScrollViewBox();
    cocos2d::Node* createCheatButton(const std::string& title, std::function<void()> action);
    cocos2d::Node* createCloseButton(const std::string& title);

    float sumContentSizeHeight(cocos2d::Node* node) const;

    static SelectStageWindow* s_ins;
    std::shared_ptr<RecruitContext> _recruitContext;
};

#endif // __SelectStageWindow_H__
