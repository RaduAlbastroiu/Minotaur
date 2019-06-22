#pragma once

#include "cocos2d.h"
#include "Updatable.h"
#include "Enemy.h"

USING_NS_CC;
using namespace std;

class EnemiesCollection : public Updatable
{
public:
  EnemiesCollection(Updater* updater);
  void AddEnemy(cocos2d::Scene* aScene, float X, float Y);
  void AttackCollection();
  int GetNumberKilled();
  void SetHero(Hero* aHero);

private:

  void DoUpdate(float delta) override;

  Hero* mHero;

  int mHitAtOnceMax = 2;

  int killed = 0;

  vector<unique_ptr<Enemy>> mEnemies;
};

