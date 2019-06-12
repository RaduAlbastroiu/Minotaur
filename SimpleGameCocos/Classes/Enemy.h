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

enum enemyState
{
  attack,
  move,
  idle,
  hit,
  dead
};

class Enemy
{
public:
  Enemy(cocos2d::Scene* aScene, float X, float Y);
  
  void TakeDamage(float damage);
  pair<float, float> GetPosition();
  void MoveAt(float X, float Y);
  bool Attack();
  void ChangeState(enemyState aNewState);
  bool DidProvokeDamage();
  void Update(float delta);
  bool IsAlive();

  enemyState GetState();

private:

  struct position
  {
    float x, y;
  };

  void Init();
  void RunAnimation(vector<string>& aAnimSprites, int aNrRuns, float aFreq);
  
  float mHealth = 100;
  cocos2d::Action* mLastAction;

  int mDirection = 0;

  bool provokeDamage = false;
  bool mIsAlive = true;
  bool mIsVisible = true;
  float mTimePassed = 0;
  float mAttackTimeStart = -0.5;
  float mDeadTimeStart = -0.5;
  float mHitTimeStart = -0.5;

  float mAttackFrecv = 0.05f;
  float mIdleFrecv = 0.15f;
  float mMoveFrecv = 0.065f;
  float mDeadFrecv = 0.1f;
  float mHitFrecv = 0.1f;

  cocos2d::Scene* mScene;
  cocos2d::Sprite* mEnemy;

  enemyState mCurrentState = enemyState::idle;
  position mCurrentPosition;

  vector<string> mEnemyIdle = { "idle_0.png",
    "idle_1.png" ,
    "idle_2.png" ,
    "idle_3.png" ,
    "idle_4.png" ,
    "idle_5.png" ,
    "idle_6.png" ,
    "idle_7.png" ,
    "idle_8.png" ,
    "idle_9.png" , 
    "idle_10.png"};

  vector<string> mEnemyHit = { "hit_0.png",
    "hit_1.png" ,
    "hit_2.png" ,
    "hit_3.png" ,
    "hit_4.png" ,
    "hit_5.png" ,
    "hit_6.png" ,
    "hit_7.png" };

  vector<string> mEnemyAttack = { "attack_0.png",
    "attack_1.png" ,
    "attack_2.png" ,
    "attack_3.png" ,
    "attack_4.png" ,
    "attack_5.png" ,
    "attack_6.png" ,
    "attack_7.png" ,
    "attack_8.png" ,
    "attack_9.png" ,
    "attack_10.png",
    "attack_11.png", 
    "attack_12.png", 
    "attack_13.png", 
    "attack_14.png", 
    "attack_15.png", 
    "attack_16.png", 
    "attack_17.png"};

  vector<string> mEnemyDead = { "dead_0.png",
    "dead_1.png" ,
    "dead_2.png" ,
    "dead_3.png" ,
    "dead_4.png" ,
    "dead_5.png" ,
    "dead_6.png" ,
    "dead_7.png" ,
    "dead_8.png" ,
    "dead_9.png" ,
    "dead_10.png",
    "dead_11.png",
    "dead_12.png",
    "dead_13.png" };

  vector<string> mEnemyMove = { "walk_0.png",
    "walk_1.png" ,
    "walk_2.png" ,
    "walk_3.png" ,
    "walk_4.png" ,
    "walk_5.png" ,
    "walk_6.png" ,
    "walk_7.png" ,
    "walk_8.png" ,
    "walk_9.png" ,
    "walk_10.png",
    "walk_11.png",
    "walk_12.png"};
};

