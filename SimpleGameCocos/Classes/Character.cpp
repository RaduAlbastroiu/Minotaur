
#include "Character.h"

void Character::TakeDamage(int damage)
{
  health -= damage;
}

bool Character::IsAlive()
{
  return health > 0;
}

int Character::GetHealth()
{
  return health;
}

cocos2d::Sprite* Character::GetSprite()
{
  return sprite;
}

pair<float, float> Character::GetPosition()
{
  return make_pair(currentPosition.x, currentPosition.y);
}

void Character::RunAnimation(vector<string>& aAnimSprites, int aNrRuns, float aFrecv)
{
  auto spritecache = SpriteFrameCache::getInstance();
  Vector<SpriteFrame*> anim;
  for (int i = 0; i < aAnimSprites.size(); i++)
  {
    anim.pushBack(spritecache->getSpriteFrameByName(aAnimSprites[i]));
  }
  auto animation = Animation::createWithSpriteFrames(anim, aFrecv);
  cocos2d::Action* action = Repeat::create(Animate::create(animation), aNrRuns);
  lastAction = action;
  sprite->runAction(action);
}

void Character::ChangeState(internalState newState)
{
  if (currentState == internalState::idle)
  {
    if (newState == internalState::move)
    {
      currentState = internalState::move;
      sprite->stopAction(lastAction);
      RunMoveAnimation();
    }
    if (newState == internalState::attack)
    {
      currentState = internalState::attack;
      sprite->stopAction(lastAction);
      RunAttackAnimation();
    }
    if (newState == internalState::dead)
    {
      currentState = internalState::dead;
      timeDeadPassed = timePassed;
      sprite->stopAction(lastAction);
      RunDeadAnimation();
    }
  }
  if (currentState == internalState::move)
  {
    if (newState == internalState::idle)
    {
      currentState = internalState::idle;
      sprite->stopAction(lastAction);
      RunIdleAnimation();
    }
    if (newState == internalState::attack)
    {
      currentState = internalState::attack;
      sprite->stopAction(lastAction);
      RunAttackAnimation();
    }
    if (newState == internalState::dead)
    {
      currentState = internalState::dead;
      timeDeadPassed = timePassed;
      sprite->stopAction(lastAction);
      RunDeadAnimation();
    }
  }
  if (currentState == internalState::attack)
  {
    if (newState == internalState::idle)
    {
      currentState = internalState::idle;
      sprite->stopAction(lastAction);
      RunIdleAnimation();
    }
    if (newState == internalState::move)
    {
      currentState = internalState::move;
      sprite->stopAction(lastAction);
      RunMoveAnimation();
    }
    if (newState == internalState::dead)
    {
      currentState = internalState::dead;
      timeDeadPassed = timePassed;
      sprite->stopAction(lastAction);
      RunDeadAnimation();
    }
  }
  if (currentState == internalState::hit)
  {
    if (newState == internalState::idle)
    {
      currentState = internalState::idle;
      sprite->stopAction(lastAction);
      RunIdleAnimation();
    }
  }

  if (newState == internalState::hit && currentState != newState && currentState != internalState::dead)
  {
    currentState = newState;
    sprite->stopAction(lastAction);
    timeHitPassed = timePassed;
    RunHitAnimation();
  }
}
