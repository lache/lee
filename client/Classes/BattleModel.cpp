#include "BattleModel.h"
#include "PopText.h"
#include "RecruitButton.h"
#include "SelectStageButton.h"
#include "Actor.h"
#include "BattleResultWindow.h"
#include "cocos2d.h"
USING_NS_CC;

BattleModel::BattleModel()
    : _team1Size(0),
    _team2Size(0)
{
}

BattleModel::~BattleModel()
{
}

void BattleModel::setTeamSize(int team1, int team2)
{
    _team1Size = team1;
    _team2Size = team2;
}
void BattleModel::onActorDead(Actor* a)
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

void BattleModel::onTeam1Eliminated()
{
    BattleResultWindow::open(false, 10);
}

void BattleModel::onTeam2Eliminated()
{
    BattleResultWindow::open(true, 100);
}
