#pragma once

#include "cocos2d.h"
#include "Includes.h"
#include "Updateable.h"
#include "KeyboardListener.h"


class Character : public Updateable
{
public:

  virtual void Attack();
  virtual void TakeDamage(int damage);
  virtual bool IsAlive();

  virtual cocos2d::Sprite* GetSprite();

  virtual pair<float, float> GetPosition();

protected:

  enum internalState
  {
    attack,
    move,
    idle,
    hit,
    dead
  };
  internalState currentState = internalState::idle;

  virtual void RunAttackAnimation() = 0;
  virtual void RunIdleAnimation() = 0;
  virtual void RunMoveAnimation() = 0;
  virtual void RunHitAnimation() = 0;
  virtual void RunDeadAnimation() = 0;
  void RunAnimation(vector<string>& aAnimSprites, int aNrRuns, float aFrecv);
  void ChangeState(internalState newState);

  cocos2d::Sprite* characterSprite;
  cocos2d::Action* lastAction;

  int health = 100;
  float timeAttackStart = 0;
  float timeDeadStart = 0;
  float timeHitStart = 0;
};
