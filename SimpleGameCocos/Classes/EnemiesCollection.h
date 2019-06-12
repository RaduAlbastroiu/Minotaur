#pragma once

#include "cocos2d.h"
#include "Enemy.h"

USING_NS_CC;
using namespace std;

class EnemiesCollection
{
public:

  void AddEnemy(cocos2d::Scene* aScene, float X, float Y);
  void AttackAt(float X, float Y, int aForce);
  int GetNumberKilled();
  void Reset();
  void Update(float delta);

  void SetHero(Hero* aHero);

private:

  Hero* mHero;

  float mDistAttack = 175;
  float mDistForEnemy = 125;
  float mMinDistance = 100;
  float mSpeed = 2.0f;

  int mHitAtOnceMax = 1;

  int killed = 0;

  vector<unique_ptr<Enemy>> mEnemies;
};

