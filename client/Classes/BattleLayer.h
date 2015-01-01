#ifndef __BattleLayer_SCENE_H__
#define __BattleLayer_SCENE_H__

#include "cocos2d.h"

class RecruitContext;

class BattleLayer : public cocos2d::Layer
{
public:
    virtual bool init();

    static cocos2d::Scene* scene(std::shared_ptr<RecruitContext> recruitContext);

    // implement the "static node()" method manually
    CREATE_FUNC(BattleLayer);

private:
    void setRecruitContext(std::shared_ptr<RecruitContext> recruitContext);
    void resetBattleground();
    void spawnActor(int team);

    Node* _battleground;
};

#endif // __BattleLayer_SCENE_H__
