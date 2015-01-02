#ifndef __BattleLayer_SCENE_H__
#define __BattleLayer_SCENE_H__

#include "cocos2d.h"

class RecruitContext;
class BattleContext;

class BattleLayer : public cocos2d::Layer
{
public:
    virtual bool init();

    static cocos2d::Scene* scene(int stageId, const std::shared_ptr<RecruitContext>& recruitContext);

    // implement the "static node()" method manually
    CREATE_FUNC(BattleLayer);

private:
    void resetBattleground();
    void spawnActor(int team);
    void createBattleContext(const std::shared_ptr<RecruitContext>& recruitContext);
    void initBattleContext(int stageId, const std::shared_ptr<RecruitContext>& recruitContext);
    Node* _battleground;
    int _stageId;
    std::shared_ptr<BattleContext> _battleContext;
};

#endif // __BattleLayer_SCENE_H__
