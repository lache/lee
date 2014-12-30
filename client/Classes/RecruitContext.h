#pragma once

namespace cocos2d { class Node; }

class RecruitButton;

class RecruitContext
{
public:
    RecruitContext();
    ~RecruitContext();

    void startRecruit(cocos2d::Node* ground, const int targetRecruitSize);
    void setRecruitButton(RecruitButton* recruitButton) { _recruitButton = recruitButton; }
    int getCurrentRecruitSize() const { return _currentRecruitSize; }

private:
    void onRecruitArrived(cocos2d::Node* ground, cocos2d::Node* fighter);
    void onRecruitFinished();

    int _targetRecruitSize;
    int _currentRecruitSize;
    RecruitButton* _recruitButton;
};
