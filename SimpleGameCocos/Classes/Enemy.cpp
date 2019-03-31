#pragma once
#include "Enemy.h"


Enemy::Enemy(cocos2d::Scene * scene, float X, float Y)
{
  mScene = scene;

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
  ChangeState(enemyState::hit);
}

pair<float, float> Enemy::GetPosition()
{
  return make_pair(mEnemy->getPositionX(), mEnemy->getPositionY());
}

void Enemy::MoveAt(float X, float Y)
{
  if (mCurrentState!= enemyState::dead && mCurrentState != enemyState::hit)
  {
    ChangeState(enemyState::move);
    auto moveBy = MoveBy::create(0.01667f, Vec2(X, Y));
    mEnemy->runAction(moveBy);
  }
}

void Enemy::Update(float delta)
{
  mTimePassed += delta;

  if (mTimePassed - mDeadTimeStart > 1 && mCurrentState == enemyState::dead && mIsAlive == true)
  {
    mIsAlive = false;
  }

  if (mTimePassed - mDeadTimeStart > 2.5 && mCurrentState == enemyState::dead && mIsVisible == true)
  {
    mIsVisible = false;
    mEnemy->setOpacity(255);
    auto fadeOut = CCFadeOut::create(1.0f);
    mEnemy->runAction(fadeOut);
  }

  if (mHealth <= 0 && mCurrentState != enemyState::dead)
  {
    ChangeState(enemyState::dead);
  }

  if (mCurrentState == enemyState::hit && mTimePassed - mHitAttackTimeStart > 0.3f)
  {
    ChangeState(enemyState::idle);
  }


}

bool Enemy::IsAlive()
{
  return mIsAlive;
}

void Enemy::Init()
{
  SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Skeleton/SkeletonFinal.plist");
  RunAnimation(mEnemyIdle, 1000, mIdleFrecv);
  mScene->addChild(mEnemy, 2);
}

void Enemy::RunAnimation(vector<string>& aAnimSprites, int aNrRuns, float aFreq)
{
  auto spritecache = SpriteFrameCache::getInstance();
  Vector<SpriteFrame *> anim;
  for (int i = 0; i < aAnimSprites.size(); i++)
  {
    anim.pushBack(spritecache->getSpriteFrameByName(aAnimSprites[i]));
  }
  auto animation = Animation::createWithSpriteFrames(anim, aFreq);
  cocos2d::Action* action = Repeat::create(Animate::create(animation), aNrRuns);
  mLastAction = action;
  mEnemy->runAction(action);
}

void Enemy::ChangeState(enemyState aNewState)
{
  if (aNewState == enemyState::dead)
  {
    mCurrentState = aNewState;
    mDeadTimeStart = mTimePassed;
    mEnemy->stopAction(mLastAction);
    RunAnimation(mEnemyDead, 1, mDeadFrecv);
  }

  if (mCurrentState != enemyState::dead && mCurrentState != enemyState::hit)
  {
    if (aNewState == enemyState::idle && mCurrentState != enemyState::idle)
    {
      mCurrentState = aNewState;
      mEnemy->stopAction(mLastAction);
      RunAnimation(mEnemyIdle, 1000, mIdleFrecv);
    }

    if (aNewState == enemyState::hit && mCurrentState != enemyState::hit)
    {
      mCurrentState = aNewState;
      mEnemy->stopAction(mLastAction);
      mHitAttackTimeStart = mTimePassed;
      RunAnimation(mEnemyHit, 1, mHitFrecv);
    }

    if (aNewState == enemyState::move && mCurrentState != enemyState::move)
    {
      mCurrentState = aNewState;
      mEnemy->stopAction(mLastAction);
      RunAnimation(mEnemyMove, 1000, mMoveFrecv);
    }
  }
}

enemyState Enemy::GetState()
{
  return mCurrentState;
}
