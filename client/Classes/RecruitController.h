#ifndef __RecruitController_H__
#define __RecruitController_H__

#include "Typedefs.h"
#include "ErrorCode.h"

class RecruitController
{
public:
    static ErrorCode Recruit(PlayerModelPtr player);
    static ErrorCode StopRecruit(PlayerModelPtr player);
};

#endif
