#pragma once
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

pair<float, float> Enemy::GetPosition()
{
  return make_pair(mCurrentPosition.x, mCurrentPosition.y);
}

void Enemy::Update(float delta)
{
  mTimePassed += delta;

  if (mHealth <= 0 && mCurrentState != enemyState::dead)
  {
    ChangeState(enemyState::dead);
  }
}

void Enemy::Init()
{
  SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Skeleton/SkeletonFinal.plist");
  RunAnimation(mEnemyIdle, 1000);
  mScene->addChild(mEnemy, 2);
}

void Enemy::RunAnimation(vector<string> aAnimSprites, int aNrRuns)
{
  auto spritecache = SpriteFrameCache::getInstance();
  Vector<SpriteFrame *> anim;
  for (int i = 0; i < aAnimSprites.size(); i++)
  {
    anim.pushBack(spritecache->getSpriteFrameByName(aAnimSprites[i]));
  }
  auto animation = Animation::createWithSpriteFrames(anim, 0.1);
  cocos2d::Action* action = Repeat::create(Animate::create(animation), aNrRuns);
  mLastAction = action;
  mEnemy->runAction(action);
}

void Enemy::ChangeState(enemyState aNewState)
{
  if (aNewState == enemyState::dead)
  {
    mCurrentState = aNewState;
    mEnemy->stopAction(mLastAction);
    RunAnimation(mEnemyDead, 1);
  }
}
