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
  
  cocos2d::Sprite* aHero;
  cocos2d::Animation* AttackAnimation;

  vector<string> str = { "MinotaurAttack_0.png",
  "MinotaurAttack_1.png" ,
  "MinotaurAttack_2.png" ,
  "MinotaurAttack_3.png" ,
  "MinotaurAttack_4.png" ,
  "MinotaurAttack_5.png" ,
  "MinotaurAttack_6.png" ,
  "MinotaurAttack_7.png" ,
  "MinotaurAttack_8.png" };

  cocos2d::Scene* mScene;
  cocos2d::Sprite* mCurrentSprite;

  struct position
  {
    float x, y;
  };
  position mCurrentPosition;
  float speed;
  float animationDuration;

  enum HeroState
  {
    attack,
    move,
    stand
  };
  HeroState mCurrentState;
  float numberOfRunsAnimation;

  float lastAnimationTime;
  float timePassed;

  vector<cocos2d::Sprite*> mMoveAnimation;
  vector<cocos2d::Sprite*> mAttackAnimation;
  vector<cocos2d::Sprite*> mStandingAnimation;

  int mCurrentMoveSprite;
  int mCurrentAttackSprite;
  int mCurrentStangindSprite;

  void ResetCurrentSprite();
  void DrawNextMoveAnimation(position aPosition);
  void DrawNextAttackAnimation(position aPosition);
  void DrawNextStandingAnimation(position aPosition);

  cocos2d::Sprite* GetMinotaurAt(int x, int y);
};
