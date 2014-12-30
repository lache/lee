#include "RecruitContext.h"
#include "PopText.h"
#include "RecruitButton.h"
#include "cocos2d.h"
USING_NS_CC;

RecruitContext::RecruitContext()
    : _targetRecruitSize(0),
    _currentRecruitSize(0),
    _recruitButton(nullptr)
{
}

RecruitContext::~RecruitContext()
{
}

void RecruitContext::startRecruit(cocos2d::Node* ground, const int targetRecruitSize)
{
    _targetRecruitSize += targetRecruitSize;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    std::mt19937 generator;

    generator.seed(1985);

    std::uniform_real_distribution<float> distribution(0, static_cast<float>(2 * M_PI));
    auto twoPi = std::bind(distribution, generator);

    std::mt19937 generator2;
    generator2.seed(1981);
    std::uniform_real_distribution<float> zeroOneDistribution(0, 1);
    auto zeroOne = std::bind(zeroOneDistribution, generator2);
    
    for (int i = 0; i < targetRecruitSize; ++i)
    {
        auto theta = twoPi();
        auto delay = zeroOne() * 5;

        auto rat = theta / delay;

        auto fighter01 = Sprite::create();
        auto radius = 350;
        fighter01->setPosition(origin + visibleSize / 2 + radius * Vec2(cosf(theta), sinf(theta)));
        fighter01->runAction(RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("fighter01"))));
        fighter01->runAction(Sequence::create(
            DelayTime::create(delay),
            MoveTo::create(1, origin + visibleSize / 2),
            DelayTime::create(0.1f),
            CallFunc::create([=]() { onRecruitArrived(ground, fighter01); }),
            RemoveSelf::create(),
            nullptr));

        ground->addChild(fighter01);
    }
}

void RecruitContext::onRecruitArrived(Node* ground, Node* fighter)
{
    PopText::create(ground, fighter->getPosition(), "+1");

    _currentRecruitSize++;

    if (_recruitButton)
    {
        _recruitButton->setButtonState(RecruitButton::ButtonState::RECRUIT_IN_PROGRESS, _currentRecruitSize);
    }

    if (_currentRecruitSize >= _targetRecruitSize)
    {
        onRecruitFinished();
    }
}

void RecruitContext::onRecruitFinished()
{
    if (_recruitButton)
    {
        _recruitButton->setButtonState(RecruitButton::ButtonState::CAN_RECRUIT, _currentRecruitSize);
    }
}
