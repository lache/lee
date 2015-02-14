#ifndef __BattleLayer_SCENE_H__
#define __BattleLayer_SCENE_H__

#include "cocos2d.h"
#include "Typedefs.h"

class BattleLayer : public cocos2d::Layer
{
public:
    virtual bool init();

    static cocos2d::Scene* scene(int stageId, const PlayerModelPtr& playerModel);

    // implement the "static node()" method manually
    CREATE_FUNC(BattleLayer);

private:
    void resetBattleground();
    void spawnActor(int team);
    void createBattleContext(const PlayerModelPtr& playerModel);
    void initBattleContext(int stageId, const PlayerModelPtr& playerModel);
    Node* _battleground;
    int _stageId;
    BattleModelPtr _battleModel;
};

#endif // __BattleLayer_SCENE_H__
