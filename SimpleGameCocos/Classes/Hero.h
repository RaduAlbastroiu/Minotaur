#pragma once

#include "cocos2d.h"
#include "MoveableEntity.h"

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
  Hero(cocos2d::Scene* scene, float positionX, float positionY);

  void Attack();
  void SetMoveDirection(int direction);

  void Update(float delta);

private:

  void Init();
  void RunIdleAnimation();
  void RunMoveAnimation();
  void RunAttackAnimation();

  cocos2d::Action* mIdleAction;
  cocos2d::Action* mMoveAction;
  cocos2d::Action* mAttackAction;

  struct position
  {
    float x, y;
  };

  enum heroState
  {
    attack,
    move,
    idle
  };

  int mDirection = 0;

  float mTimePassed = 0;

  cocos2d::Scene* mScene;
  cocos2d::Sprite* mHero;

  bool started = false;

  heroState mCurrentState = heroState::idle;
  position mCurrentPosition;
  float mSpeed = 10;;

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

  vector<string> mHeroMove = { "MinotaurMove_0.png",
  "MinotaurMove_1.png" ,
  "MinotaurMove_2.png" ,
  "MinotaurMove_3.png" ,
  "MinotaurMove_4.png" ,
  "MinotaurMove_5.png" ,
  "MinotaurMove_6.png" ,
  "MinotaurMove_7.png" };
};
