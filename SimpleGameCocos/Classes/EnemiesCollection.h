#pragma once

#include "cocos2d.h"
#include "Enemy.h"

USING_NS_CC;
using namespace std;

class EnemiesCollection
{
public:

  void AddEnemy(cocos2d::Scene* aScene, Hero * aHero, float X, float Y);
  void AttackAt(float X, float Y, int aForce);
  void Update(float delta);

private:

  float mDistAttack = 125;

  vector<unique_ptr<Enemy>> mEnemies;
};

