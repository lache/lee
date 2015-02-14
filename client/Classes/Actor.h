#ifndef __Actor_H__
#define __Actor_H__

#include "cocos2d.h"

class BattleModel;

class Actor : public cocos2d::Sprite
{
public:
    static Actor* create(int team, const std::shared_ptr<BattleModel>& battleContext);

	void setHp(float hp) { _hp = hp; }
	void setMoveSpeed(float moveSpeed) { _moveSpeed = moveSpeed; }
	void setAttackPower(float attackPower) { _attackPower = attackPower; }
    int getTeam() const { return _team; }
	static void cleanupActors() { s_actors.clear(); }

CC_CONSTRUCTOR_ACCESS:
    virtual bool init(int team, const std::shared_ptr<BattleModel>& battleContext);

	virtual void update(float delta) override;

private:
	void tryFindNewTarget();
	void tryAttackTarget();
	void attackTarget();
    void onActorDead();

	bool isValidAttackTarget(Actor* a);

	int _team;
	Actor* _target;
	float _attackRangeNear;
	float _attackRangeFar;
	float _moveSpeed;
	float _attackWait;
	float _attackWait0;
	float _hp;
	float _attackPower;
	bool _approachingToTarget;
    std::shared_ptr<BattleModel> _battleContext;

	static cocos2d::Vector<Actor*> s_actors;
};

#endif // __Actor_H__
