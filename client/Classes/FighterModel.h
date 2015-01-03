#ifndef __FighterModel_H__
#define __FighterModel_H__

#include "Typedefs.h"
#include "ActorModel.h"

class FighterModel : public ActorModel
{
public:
    // copy from template
    float _maxHp;

    float _attack;
    float _attackRange;
    float _attackInterval;
    float _moveSpeed;

    float _weight; // ���� (�󸶳� ž�� ����)

    // set by logic
    float _hp;

    FighterModelPtr Clone()
    {
        return FighterModelPtr(new FighterModel(*this));
    }
};

#endif
