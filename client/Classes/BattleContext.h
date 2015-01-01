#pragma once

namespace cocos2d { class Node; }

class RecruitButton;
class SelectStageButton;

class BattleContext
{
public:
    BattleContext();
    ~BattleContext();

    void startRecruit(cocos2d::Node* ground, const int targetRecruitSize);
    void setRecruitButton(RecruitButton* recruitButton) { _recruitButton = recruitButton; }
    void setSelectStageButton(SelectStageButton* selectStageButton) { _selectStageButton = selectStageButton; }
    int getCurrentRecruitSize() const { return _currentRecruitSize; }

private:
    void onRecruitArrived(cocos2d::Node* ground, cocos2d::Node* fighter);
    void onRecruitFinished();

    int _targetRecruitSize;
    int _currentRecruitSize;
    RecruitButton* _recruitButton;
    SelectStageButton* _selectStageButton;
};
