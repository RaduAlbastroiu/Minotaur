#pragma once

#include "EnemiesCollection.h"

void EnemiesCollection::AddEnemy(cocos2d::Scene * aScene, Hero * aHero, float X, float Y)
{
  mEnemies.push_back(make_unique<Enemy>(Enemy(aScene, aHero, X, Y)));
}

void EnemiesCollection::AttackAt(float X, float Y, int aForce)
{
  auto heroPoint = Point(X, Y);
  for (auto& enemy : mEnemies)
  {
    auto posEnemy = enemy->GetPosition();
    auto enemyPoint = Point(posEnemy.first, posEnemy.second);

    auto dist = heroPoint.getDistance(enemyPoint);
    
    if (dist < mDistAttack)
    {
      enemy->TakeDamage((rand() % (aForce/2)) + aForce);
    }
  }
}

void EnemiesCollection::Update(float delta)
{
  for (auto& enemy : mEnemies)
  {
    enemy->Update(delta);
  }
}
