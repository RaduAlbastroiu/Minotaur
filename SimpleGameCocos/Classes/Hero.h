#pragma once

#include "cocos2d.h"

#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4
#define NODIRECTION -1

USING_NS_CC;
using namespace std;

class Hero : public cocos2d::Node
{
public:
  Hero(cocos2d::Scene* scene);

  void Attack();
  void SetMoveDirection(int direction);
  void TakeDamage(float damage);
  void Update(float delta);
  
private:

  float mHealth = 100;

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
    dead
  };

  void Init();
  void RunIdleAnimation();
  void RunMoveAnimation();
  void RunAttackAnimation();
  void RunDeadAnimation();

  void ChangeState(heroState newState);
  void MovePosition();

  int mDirection = 0;

  float mTimePassed = 0;
  float mAttackTimeStart = -0.5;
  float mDeadTimeStart = -0.5;

  cocos2d::Scene* mScene;
  cocos2d::Sprite* mHero;

  heroState mCurrentState = heroState::idle;
  position mCurrentPosition;
  float mSpeed = 4;

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
