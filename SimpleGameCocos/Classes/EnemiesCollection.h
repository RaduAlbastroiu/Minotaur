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
  bool CanMoveAt(float curetnX, float currentY, float X, float Y);
  int GetNumberKilled();
  void Update(float delta);

  void SetHero(Hero* aHero);

private:

  Hero* mHero;

  float mDistAttack = 175;
  float mDistForEnemy = 125;
  float mMinDistance = 100;
  float mSpeed = 2.0f;

  int mHitAtOnceMax = 1;

  vector<unique_ptr<Enemy>> mEnemies;
};

