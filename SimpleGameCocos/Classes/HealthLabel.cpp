#include "HealthLabel.h"

HealthBar::HealthBar()
{
  mHealthSprite = cocos2d::Sprite::create(mLifeBar[10]);
  mHealthSprite->setScale(0.4f);
  mHealthSprite->setPosition(Director::getInstance()->getVisibleSize().width / 9, Director::getInstance()->getVisibleSize().height / 1.07);
}

cocos2d::Sprite* HealthBar::GetLabel()
{
  return mHealthSprite;
}

void HealthBar::UpdateValue(int health)
{
  mHealthSprite->setTexture(mLifeBar[health / 10]);
}
