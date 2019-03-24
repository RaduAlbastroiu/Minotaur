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
  SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Minotaur.plist");
  RunIdleAnimation();
  mScene->addChild(mEnemy);
}

void Enemy::RunIdleAnimation()
{
  auto spritecache = SpriteFrameCache::getInstance();
  Vector<SpriteFrame *> animIdle;
  for (int i = 0; i < 5; i++)
  {
    animIdle.pushBack(spritecache->getSpriteFrameByName(mEnemyIdle[i]));
  }
  auto idleAnimation = Animation::createWithSpriteFrames(animIdle, 0.175);
  cocos2d::Action* action = RepeatForever::create(Animate::create(idleAnimation));
  mLastAction = action;
  mEnemy->runAction(action);
}
