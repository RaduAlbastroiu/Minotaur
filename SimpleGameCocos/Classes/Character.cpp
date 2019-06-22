
#include "Character.h"

Character::Character(Updater* updater)
  :Updatable(updater)
{
}

void Character::Attack()
{
  if (currentState != internalState::attack && currentState != internalState::hit && currentState != internalState::dead)
  {
    timeAttackStart = timePassed;
    ChangeState(internalState::attack);
  }
}

void Character::TakeDamage(int damage)
{
  health -= damage;
  health = max(0, health);
  ChangeState(internalState::hit);
}

bool Character::IsAlive()
{
  return health > 0;
}

cocos2d::Sprite* Character::GetSprite()
{
  return characterSprite;
}

pair<float, float> Character::GetPosition()
{
  return make_pair(characterSprite->getPositionX(), characterSprite->getPositionY());
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
  characterSprite->runAction(action);
}

void Character::ChangeState(internalState newState)
{
  if (currentState == internalState::idle)
  {
    if (newState == internalState::move)
    {
      currentState = internalState::move;
      characterSprite->stopAction(lastAction);
      RunMoveAnimation();
    }
    if (newState == internalState::attack)
    {
      currentState = internalState::attack;
      characterSprite->stopAction(lastAction);
      RunAttackAnimation();
    }
    if (newState == internalState::dead)
    {
      currentState = internalState::dead;
      timeDeadStart = timePassed;
      characterSprite->stopAction(lastAction);
      RunDeadAnimation();
    }
  }
  if (currentState == internalState::move)
  {
    if (newState == internalState::idle)
    {
      currentState = internalState::idle;
      characterSprite->stopAction(lastAction);
      RunIdleAnimation();
    }
    if (newState == internalState::attack)
    {
      currentState = internalState::attack;
      characterSprite->stopAction(lastAction);
      RunAttackAnimation();
    }
    if (newState == internalState::dead)
    {
      currentState = internalState::dead;
      timeDeadStart = timePassed;
      characterSprite->stopAction(lastAction);
      RunDeadAnimation();
    }
  }
  if (currentState == internalState::attack)
  {
    if (newState == internalState::idle)
    {
      currentState = internalState::idle;
      characterSprite->stopAction(lastAction);
      RunIdleAnimation();
    }
    if (newState == internalState::move)
    {
      currentState = internalState::move;
      characterSprite->stopAction(lastAction);
      RunMoveAnimation();
    }
    if (newState == internalState::dead)
    {
      currentState = internalState::dead;
      timeDeadStart = timePassed;
      characterSprite->stopAction(lastAction);
      RunDeadAnimation();
    }
  }
  if (currentState == internalState::hit)
  {
    if (newState == internalState::idle)
    {
      currentState = internalState::idle;
      characterSprite->stopAction(lastAction);
      RunIdleAnimation();
    }
  }

  if (newState == internalState::hit && currentState != newState && currentState != internalState::dead)
  {
    currentState = newState;
    characterSprite->stopAction(lastAction);
    timeHitStart = timePassed;
    RunHitAnimation();
  }
}
