#pragma once

#include <vector>
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class Hero
{
public:
  Hero();
  Hero(cocos2d::Scene* scene, float positionX, float positionY);

  void MoveToPosition(float x, float y);
  void Attack(int type);
  void Update(float delta);

private:

  void Init();
  void InitIdleAnimation();
  void InitMoveAnimation();
  void InitAttackAnimation();

  struct position
  {
    float x, y;
  };

  enum heroState
  {
    attack,
    move,
    stand
  };

  float mTimePassed = 0;

  cocos2d::Scene* mScene;
  cocos2d::Sprite* mHero;

  bool started = false;

  cocos2d::Animation* mIdleAnimation;
  cocos2d::Animation* mMoveAnimation;
  cocos2d::Animation* mAttackAnimation;

  heroState mCurrentState = heroState::stand;
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
