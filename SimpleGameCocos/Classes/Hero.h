#pragma once

#include "cocos2d.h"
#include "Includes.h"
#include "KeyboardListener.h"

USING_NS_CC;
using namespace std;

class EnemiesCollection;

class Hero
{
public:
  Hero(cocos2d::Scene* scene, EnemiesCollection* aEnemiesCollection, KeyboardListener* aKeyboardListener);

  void Attack();
  void TakeDamage(int damage);
  bool IsAlive();
  void Reset();
  void Update(float delta);
  void GetKeyboardInput();
  int GetHealth();

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

  enum heroState
  {
    attack,
    move,
    idle, 
    hit,
    dead
  };

  void Init();
  void RunAnimation(vector<string>& aAnimSprites, int aNrRuns, float aFrecv);

  void ChangeState(heroState newState);
  void MovePosition();

  int mDirection = 0;

  float mTimePassed = 0;
  float mAttackTimeStart = -0.5;
  float mDeadTimeStart = -0.5;
  float mHitTimeStart = -0.5;

  float mAttackFrecv = 0.045f;
  float mIdleFrecv = 0.15f;
  float mMoveFrecv = 0.065f;
  float mDeadFrecv = 0.1f;
  float mHitFrecv = 0.1f;

  cocos2d::Scene* mScene;
  cocos2d::Sprite* mHero;

  EnemiesCollection* mEnemiesCollection;

  heroState mCurrentState = heroState::idle;
  position mCurrentPosition;
  float mSpeed = 6;

  vector<string> mHeroAttack = { "MinotaurAttack_0.png",
  "MinotaurAttack_1.png" ,
  "MinotaurAttack_2.png" ,
  "MinotaurAttack_3.png" ,
  "MinotaurAttack_4.png" ,
  "MinotaurAttack_5.png" ,
  "MinotaurAttack_6.png" ,
  "MinotaurAttack_7.png" ,
  "MinotaurAttack_8.png" };

  vector<string> mHeroIdle = { "MinotaurIdle_0.png",
  "MinotaurIdle_1.png" ,
  "MinotaurIdle_2.png" ,
  "MinotaurIdle_3.png" ,
  "MinotaurIdle_4.png" };

  vector<string> mHeroDead = { "MinotaurDead_0.png",
  "MinotaurDead_1.png" ,
  "MinotaurDead_2.png" ,
  "MinotaurDead_3.png" ,
  "MinotaurDead_4.png" ,
  "MinotaurDead_5.png" };

  vector<string> mHeroMove = { "MinotaurMove_0.png",
  "MinotaurMove_1.png" ,
  "MinotaurMove_2.png" ,
  "MinotaurMove_3.png" ,
  "MinotaurMove_4.png" ,
  "MinotaurMove_5.png" ,
  "MinotaurMove_6.png" ,
  "MinotaurMove_7.png" };

};
