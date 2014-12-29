#ifndef __BuyAirplaneWindow_H__
#define __BuyAirplaneWindow_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"

namespace cocos2d{
    namespace ui {
        class ScrollView;
        class VBox;
    }
}

class BuyAirplaneWindow : public cocos2d::ui::RelativeBox
{
public:
    static BuyAirplaneWindow* create(const cocos2d::Size& size);

CC_CONSTRUCTOR_ACCESS:
    // Nodes should be created using create();
    BuyAirplaneWindow() {}
    virtual ~BuyAirplaneWindow() {}

    virtual bool initWithSize(const cocos2d::Size& size) override;
    virtual void onEnter() override;

public:
    void setLane(int laneId) { _laneId = laneId; }
    int getLane() const { return _laneId; }

    static BuyAirplaneWindow* s_ins;

private:
    int _laneId;
    cocos2d::ui::ScrollView* _scrollView;
    cocos2d::ui::VBox* _vBox;
};

#endif // __BuyAirplaneWindow_H__
