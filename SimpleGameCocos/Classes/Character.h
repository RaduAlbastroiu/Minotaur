#pragma once

#include "cocos2d.h"
#include "Includes.h"
#include "KeyboardListener.h"



class Character
{
public:
  Character();

  void Attack();
  void TakeDamage(int damage);
  bool IsAlive();
  void Reset();
  void Update(float delta);
  void GetKeyboardInput();
  int GetHealth();

  cocos2d::Sprite* GetSprite();

  pair<float, float> GetPosition();

private:

  bool CanMoveAt(float currentX, float currentY, float X, float Y);

  KeyboardListener* keyboardListener;

  int mHealth = 100;

  cocos2d::Action* mLastAction;

  struct position
  {
    float x, y;
  };

  enum internalState
  {
    attack,
    move,
    idle,
    hit,
    dead
  };

  void Init();
  void RunAnimation(vector<string>& aAnimSprites, int aNrRuns, float aFrecv);

  void ChangeState(internalState newState);
  void MovePosition();

  int mDirection = 0;

  float mTimePassed = 0;
  float mAttackTimeStart = -0.5;
  float mDeadTimeStart = -0.5;
  float mHitTimeStart = -0.5;

  cocos2d::Sprite* mHero;

  internalState currentState = internalState::idle;
  position mCurrentPosition;
  float mSpeed = 6;
};
