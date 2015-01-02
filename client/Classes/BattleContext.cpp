#include "BattleContext.h"
#include "PopText.h"
#include "RecruitButton.h"
#include "SelectStageButton.h"
#include "Actor.h"
#include "BattleResultWindow.h"
#include "cocos2d.h"
USING_NS_CC;

BattleContext::BattleContext()
    : _team1Size(0),
    _team2Size(0)
{
}

BattleContext::~BattleContext()
{
}

void BattleContext::setTeamSize(int team1, int team2)
{
    _team1Size = team1;
    _team2Size = team2;
}
void BattleContext::onActorDead(Actor* a)
{
    if (a->getTeam() == 1)
        _team1Size -= 1;
    else
        _team2Size -= 1;

    if (_team1Size <= 0)
        onTeam1Eliminated();
    else if (_team2Size <= 0)
        onTeam2Eliminated();
}

void BattleContext::onTeam1Eliminated()
{
    BattleResultWindow::open(false, 10);
}

void BattleContext::onTeam2Eliminated()
{
    BattleResultWindow::open(true, 100);
}
