#ifndef __ActorModel_H__
#define __ActorModel_H__

#include "ActorType.h"

// 움직이는 모든 것
class ActorModel
{
public:
    ActorType _type;

    long long /* very long */ int _actorId;
    float _x, _y;
};

#endif
