#include "Actor.h"
#include <algorithm>
#include "PopText.h"
USING_NS_CC;

Vector<Actor*> Actor::s_actors;

Actor* Actor::create(int team)
{
	Actor* a = new (std::nothrow) Actor;
	if (a && a->init(team))
	{
		a->autorelease();
		return a;
	}
	CC_SAFE_DELETE(a);
	return nullptr;
}

bool Actor::init(int team)
{
	if (Sprite::init() == false)
		return false;

	_target = nullptr;
	_team = team;
	_attackRangeNear = 40.0f;
	_attackRangeFar = 60.0f;
	_moveSpeed = 200.0f;
	_attackWait = 0;
	_attackWait0 = 1.0f;
	_hp = 10.0f;
	_attackPower = 3.0f;
	_approachingToTarget = true;

	scheduleUpdate();

	runAction(RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("fighter01"))));

	s_actors.pushBack(this);

	return true;
}

void Actor::update(float delta)
{
	Sprite::update(delta);

	if (_target == nullptr || isValidAttackTarget(_target) == false)
	{
		tryFindNewTarget();
	}
	else
	{
		auto dv = _target->getPosition() - getPosition();
		auto distToTarget = dv.length();

		if (distToTarget > _attackRangeNear && _approachingToTarget == true)
		{
			auto dvNorm = dv / distToTarget;
			setPosition(getPosition() + dvNorm * _moveSpeed * delta);
		}
		else
		{
			_approachingToTarget = false;

			if (distToTarget < _attackRangeFar)
			{
				tryAttackTarget();
			}
			else
			{
				_approachingToTarget = true;
			}
		}
	}

	if (_hp <= 0)
	{
		runAction(Sequence::create(FadeOut::create(0.1f), RemoveSelf::create(), nullptr));
	}

	_attackWait = std::max(0.0f, _attackWait - delta);
}

void Actor::tryFindNewTarget()
{
	if (_team == 0)
		return;

	for (auto a : s_actors)
	{
		if (isValidAttackTarget(a))
		{
			_target = a;
			_approachingToTarget = true;
			return;
		}
	}
}

bool Actor::isValidAttackTarget(Actor* a)
{
	return a != nullptr && a->_team != 0 && a->_team != _team && a->_hp > 0;
}

void Actor::tryAttackTarget()
{
	if (_target == nullptr || _attackWait > 0 || _target->_hp <= 0 || _attackPower <= 0)
		return;

	attackTarget();
}

void Actor::attackTarget()
{
	if (_target == nullptr)
		return;

	_target->_hp -= _attackPower;
	_attackWait = _attackWait0;

	auto damageTint1 = TintTo::create(0.1f, 255, 0, 0);
	auto damageTint2 = TintTo::create(0.2f, 255, 255, 255);
	auto damageTint = Sequence::create(damageTint1, DelayTime::create(0.1f), damageTint2, nullptr);
	
    damageTint->setTag(1);
	
    if (auto act = _target->getActionByTag(1))
		act->stop();
	
    _target->runAction(damageTint);

    auto damageText = StringUtils::format("%.0f", _attackPower);

	PopText::create(_target, Vec2(_target->getContentSize().width / 2, _target->getContentSize().height), damageText);
}
