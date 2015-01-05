#ifndef __ActorModel_H__
#define __ActorModel_H__

#include "ActorType.h"

// 움직이는 모든 것
class ActorModel
{
public:
    ActorModel()
        : _type(ActorType::None)
        , _actorId(0)
        , _x(0), _y(0)
    {}

public:
    ActorType _type;

    long long /* very long */ int _actorId;
    float _x, _y;
};

#endif
