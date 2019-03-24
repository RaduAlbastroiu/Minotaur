#pragma once

#include "cocos2d.h"
#include "Hero.h"

#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4
#define NODIRECTION -1

USING_NS_CC;
using namespace std;

class Enemy
{
public:
  Enemy(cocos2d::Scene* scene, Hero * aHero, float X, float Y);
  void TakeDamage(float damage);
  void Update(float delta);

private:

  void Init();
  void RunIdleAnimation();
 
  struct position
  {
    float x, y;
  };

  enum enemyState
  {
    attack,
    move,
    idle,
    dead
  };

  float mHealth = 100;
  cocos2d::Action* mLastAction;

  int mDirection = 0;

  float mTimePassed = 0;
  float mAttackTimeStart = -0.5;
  float mDeadTimeStart = -0.5;

  Hero* mHero;
  cocos2d::Scene* mScene;
  cocos2d::Sprite* mEnemy;

  enemyState mCurrentState = enemyState::idle;
  position mCurrentPosition;
  float mSpeed = 4;

  vector<string> mEnemyIdle = { "MinotaurAttack_0.png",
 "MinotaurAttack_1.png" ,
 "MinotaurAttack_2.png" ,
 "MinotaurAttack_3.png" ,
 "MinotaurAttack_4.png" ,
 "MinotaurAttack_5.png" ,
 "MinotaurAttack_6.png" ,
 "MinotaurAttack_7.png" ,
 "MinotaurAttack_8.png" };
};

