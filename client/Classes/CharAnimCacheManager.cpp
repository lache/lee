#include "CharAnimCacheManager.h"
#include "cocos2d.h"
USING_NS_CC;

void CharAnimCacheManager::load()
{
	auto sbnFighter01 = SpriteBatchNode::create("images/001-Fighter01.png");

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

	AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(sfvFighter01, 0.2f), "fighter01");
}
