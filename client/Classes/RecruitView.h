#pragma once

namespace cocos2d { class Node; }

class RecruitButton;
class SelectStageButton;

class RecruitView
{
public:
    RecruitView();
    ~RecruitView();

    void startRecruit(cocos2d::Node* ground, const int targetRecruitSize);
    void stopRecruit();
    void clearRecruit();
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
    cocos2d::Node* _ground;
};
