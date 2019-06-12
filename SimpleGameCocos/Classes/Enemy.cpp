
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

    if (X < 0)
      mEnemy->setFlippedX(true);
    else
      mEnemy->setFlippedX(false);

    auto moveBy = MoveBy::create(0.01667f, Vec2(X, Y));
    mEnemy->runAction(moveBy);
  }
}

bool Enemy::Attack()
{
  if (mCurrentState != enemyState::attack && mCurrentState != enemyState::hit && mCurrentState != enemyState::dead)
  {
    mAttackTimeStart = mTimePassed;
    ChangeState(enemyState::attack);
    return true;
  }
  return false;
}

void Enemy::Update(float delta)
{
  mTimePassed += delta;

  if (mTimePassed - mAttackTimeStart > 1.25f && mCurrentState == enemyState::attack)
  {
    ChangeState(enemyState::idle);
  }

  if (mTimePassed - mAttackTimeStart > 0.5f && mCurrentState == enemyState::attack)
  {
    mRegisterDamage = true;
  }

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

  if (mCurrentState == enemyState::hit && mTimePassed - mHitTimeStart > 0.7f)
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

void Enemy::ChangeState(enemyState newState)
{
  if (mCurrentState == enemyState::idle)
  {
    if (newState == enemyState::move)
    {
      mCurrentState = enemyState::move;
      mEnemy->stopAction(mLastAction);
      RunAnimation(mEnemyMove, 1000, mMoveFrecv);
    }
    if (newState == enemyState::attack)
    {
      mCurrentState = enemyState::attack;
      mEnemy->stopAction(mLastAction);
      mAttackTimeStart = mTimePassed;
      RunAnimation(mEnemyAttack, 1, mAttackFrecv);
    }
    if (newState == enemyState::dead)
    {
      mCurrentState = enemyState::dead;
      mDeadTimeStart = mTimePassed;
      mEnemy->stopAction(mLastAction);
      RunAnimation(mEnemyDead, 1, mDeadFrecv);
    }
  }
  if (mCurrentState == enemyState::move)
  {
    if (newState == enemyState::idle)
    {
      mCurrentState = enemyState::idle;
      mEnemy->stopAction(mLastAction);
      RunAnimation(mEnemyIdle, 1000, mIdleFrecv);
    }
    if (newState == enemyState::attack)
    {
      mCurrentState = enemyState::attack;
      mEnemy->stopAction(mLastAction);
      mAttackTimeStart = mTimePassed;
      RunAnimation(mEnemyAttack, 1, mAttackFrecv);
    }
    if (newState == enemyState::dead)
    {
      mCurrentState = enemyState::dead;
      mDeadTimeStart = mTimePassed;
      mEnemy->stopAction(mLastAction);
      RunAnimation(mEnemyDead, 1, mDeadFrecv);
    }
  }
  if (mCurrentState == enemyState::attack)
  {
    if (newState == enemyState::idle)
    {
      mCurrentState = enemyState::idle;
      mEnemy->stopAction(mLastAction);
      RunAnimation(mEnemyIdle, 1000, mIdleFrecv);
    }
    if (newState == enemyState::move)
    {
      mCurrentState = enemyState::move;
      mEnemy->stopAction(mLastAction);
      RunAnimation(mEnemyMove, 1000, mMoveFrecv);
    }
    if (newState == enemyState::dead)
    {
      mCurrentState = enemyState::dead;
      mDeadTimeStart = mTimePassed;
      mEnemy->stopAction(mLastAction);
      RunAnimation(mEnemyDead, 1, mDeadFrecv);
    }
  }
  if (mCurrentState == enemyState::hit)
  {
    if (newState == enemyState::idle)
    {
      mCurrentState = enemyState::idle;
      mEnemy->stopAction(mLastAction);
      RunAnimation(mEnemyIdle, 1000, mIdleFrecv);
    }
  }

  if (newState == enemyState::hit && mCurrentState != newState && mCurrentState != enemyState::dead)
  {
    mCurrentState = newState;
    mEnemy->stopAction(mLastAction);
    mHitTimeStart = mTimePassed;
    RunAnimation(mEnemyHit, 1, mHitFrecv);
  }
}

bool Enemy::GetRegisterDamageAndReset()
{
  auto b = mRegisterDamage;
  mRegisterDamage = false;
  return b;
}

enemyState Enemy::GetState()
{
  return mCurrentState;
}
