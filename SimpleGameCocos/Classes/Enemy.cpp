
#include "Enemy.h"


Enemy::Enemy(Updater* updater, float X, float Y)
  : Character(updater)
{
  characterSprite = Sprite::create("Skeleton/Skeleton.png");
  characterSprite->setPosition(Vec2(X, Y));
  characterSprite->setScale(3);
  characterSprite->setAnchorPoint(Vec2(0.5, 0.5));

  Init();
}

void Enemy::MoveAt(float X, float Y)
{
  if (currentState!= internalState::dead && currentState != internalState::hit)
  {
    ChangeState(internalState::move);

    if (X < 0)
      characterSprite->setFlippedX(true);
    else
      characterSprite->setFlippedX(false);

    auto moveBy = MoveBy::create(0.01667f, Vec2(X, Y));
    characterSprite->runAction(moveBy);
  }
}

void Enemy::Idle()
{
  ChangeState(internalState::idle);
}

void Enemy::DoUpdate(float delta)
{
  timePassed += delta;

  if (timePassed - timeAttackStart > 2.0f && currentState == internalState::attack)
  {
    provokeDamage = true;
    ChangeState(internalState::idle);
  }

  if (timePassed - timeDeadStart > 2.5 && currentState == internalState::dead && mIsVisible == true)
  {
    mIsVisible = false;
    characterSprite->setOpacity(255);
    auto fadeOut = CCFadeOut::create(1.0f);
    characterSprite->runAction(fadeOut);
  }

  if (health <= 0 && currentState != internalState::dead)
  {
    ChangeState(internalState::dead);
  }

  if (currentState == internalState::hit && timePassed - timeHitStart > 0.7f)
  {
    ChangeState(internalState::idle);
  }
}

bool Enemy::IsVisible()
{
  return mIsVisible;
}

void Enemy::Init()
{
  SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Skeleton/SkeletonFinal.plist");
  RunAnimation(mEnemyIdle, 1000, 0.15f);
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
  lastAction = action;
  characterSprite->runAction(action);
}

void Enemy::RunAttackAnimation()
{
  RunAnimation(mEnemyAttack, 1, 0.05f);
}

void Enemy::RunIdleAnimation()
{
  RunAnimation(mEnemyIdle, 1000, 0.15f);
}

void Enemy::RunMoveAnimation()
{
  RunAnimation(mEnemyMove, 1000, 0.065f);
}

void Enemy::RunHitAnimation()
{
  RunAnimation(mEnemyHit, 1, 0.1f);
}

void Enemy::RunDeadAnimation()
{
  RunAnimation(mEnemyDead, 1, 0.1f);
}

// if the enemy provoked damage to the target
bool Enemy::DidFinishAttack()
{
  auto before = provokeDamage;
  provokeDamage = false;
  return before;
}

