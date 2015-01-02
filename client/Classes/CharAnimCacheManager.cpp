#include "CharAnimCacheManager.h"
#include "cocos2d.h"
USING_NS_CC;

void LoadAnimation(const std::string& filename, const std::string& animname)
{
    auto sbnFighter01 = SpriteBatchNode::create(filename);

    const auto spWidthCount = 4;
    const auto spHeightCount = 4;
    const auto spWidth = sbnFighter01->getTexture()->getContentSizeInPixels().width / spWidthCount;
    const auto spHeight = sbnFighter01->getTexture()->getContentSizeInPixels().height / spHeightCount;
    Vector<SpriteFrame*> sfvFighter01(spWidthCount * spHeightCount);
    for (auto i = 0; i < spHeightCount; i++)
    {
        for (auto j = 0; j < spWidthCount; ++j)
        {
            sfvFighter01.pushBack(SpriteFrame::createWithTexture(
                sbnFighter01->getTexture(),
                Rect(spWidth * j, spHeight * i, spWidth, spHeight)));
        }
    }

    AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(sfvFighter01, 0.2f), animname);
}

void CharAnimCacheManager::load()
{
    LoadAnimation("images/001-Fighter01.png", "fighter01");
    LoadAnimation("images/018-Thief03.png", "thief03");
}
