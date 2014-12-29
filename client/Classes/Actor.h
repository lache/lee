#ifndef __Actor_H__
#define __Actor_H__

#include "cocos2d.h"

class Actor : public cocos2d::Sprite
{
public:
	static Actor* create(int team);

	void setHp(float hp) { _hp = hp; }
	void setMoveSpeed(float moveSpeed) { _moveSpeed = moveSpeed; }
	void setAttackPower(float attackPower) { _attackPower = attackPower; }

	static void cleanupActors() { s_actors.clear(); }

CC_CONSTRUCTOR_ACCESS:
	virtual bool init(int team);

	virtual void update(float delta) override;

private:
	void tryFindNewTarget();
	void tryAttackTarget();
	void attackTarget();

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

	static cocos2d::Vector<Actor*> s_actors;
};

#endif // __Actor_H__
