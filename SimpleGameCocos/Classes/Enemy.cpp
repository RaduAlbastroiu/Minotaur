#include "Enemy.h"


Enemy::Enemy(cocos2d::Scene * scene, Hero * aHero, float X, float Y)
{
  mScene = scene;
  mHero = aHero;

  mCurrentPosition.x = X;
  mCurrentPosition.y = Y;
  mDirection = NODIRECTION;
  mCurrentState = enemyState::idle;

  mEnemy = Sprite::create("Skeleton/Skeleton.png");
  mEnemy->setPosition(Vec2(mCurrentPosition.x, mCurrentPosition.y));
  mEnemy->setScale(3);
  mEnemy->setAnchorPoint(Vec2(0.5, 0.5));

  Init();
}

void Enemy::TakeDamage(float damage)
{
  mHealth -= damage;
}

void Enemy::Update(float delta)
{
  mTimePassed += delta;
}

void Enemy::Init()
{
  SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Skeleton/SkeletonFinal.plist");
  RunIdleAnimation();
  mScene->addChild(mEnemy, 2);
}

void Enemy::RunIdleAnimation()
{
  auto spritecache = SpriteFrameCache::getInstance();
  Vector<SpriteFrame *> anim;
  for (int i = 0; i < 11; i++)
  {
    anim.pushBack(spritecache->getSpriteFrameByName(mEnemyIdle[i]));
  }
  auto animation = Animation::createWithSpriteFrames(anim, 0.1);
  cocos2d::Action* action = RepeatForever::create(Animate::create(animation));
  mLastAction = action;
  mEnemy->runAction(action);
}
