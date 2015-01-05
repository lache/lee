#ifndef __FighterModel_H__
#define __FighterModel_H__

#include "Typedefs.h"
#include "ActorModel.h"

class FighterModel : public ActorModel
{
public:
    FighterModel()
        : _maxHp(0)
        , _attack(0)
        , _attackRange(0)
        , _attackInterval(0)
        , _moveSpeed(0)
        , _weight(0)
        , _hp(0)
    {}

public:
    float _maxHp;

    float _attack;
    float _attackRange;
    float _attackInterval;
    float _moveSpeed;

    float _weight; // 무게 (얼마나 탑승 가능)

    // set by logic
    float _hp;

    FighterModelPtr Clone()
    {
        return FighterModelPtr(new FighterModel(*this));
    }
};

#endif
