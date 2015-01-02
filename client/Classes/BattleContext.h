#pragma once

namespace cocos2d { class Node; }

class RecruitButton;
class SelectStageButton;
class Actor;

class BattleContext
{
public:
    BattleContext();
    ~BattleContext();

    void setTeamSize(int team1, int team2);
    void onActorDead(Actor* a);

private:
    void onTeam1Eliminated();
    void onTeam2Eliminated();

    int _team1Size;
    int _team2Size;
};
