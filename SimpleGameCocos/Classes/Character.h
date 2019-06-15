#pragma once

#include "cocos2d.h"
#include "Includes.h"
#include "KeyboardListener.h"


class Character
{
public:

  void Attack();
  void TakeDamage(int damage);
  bool IsAlive();
  int GetHealth();

  cocos2d::Sprite* GetSprite();

  pair<float, float> GetPosition();

private:

  struct position
  {
    float x, y;
  };
  position currentPosition;

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

  cocos2d::Sprite* sprite;
  cocos2d::Action* lastAction;

  int health = 100;
  float timeAttackStart = 0;
  float timeDeadStart = 0;
  float timeHitStart = 0;
  float timePassed = 0;;
};
