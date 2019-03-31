#pragma once

#include "EnemiesCollection.h"


void EnemiesCollection::AddEnemy(cocos2d::Scene * aScene, float X, float Y)
{
  mEnemies.push_back(make_unique<Enemy>(Enemy(aScene, X, Y)));
}

void EnemiesCollection::AttackAt(float X, float Y, int aForce)
{
  auto heroPoint = Point(X, Y);
  int count = 2;
  for (auto& enemy : mEnemies)
  {
    auto posEnemy = enemy->GetPosition();
    auto enemyPoint = Point(posEnemy.first, posEnemy.second);

    auto dist = heroPoint.getDistance(enemyPoint);
    
    if (dist < mDistAttack && count > 0)
    {
      enemy->TakeDamage(aForce);
      count--;
    }
  }
}

bool EnemiesCollection::CanMoveAt(float currentX, float currentY, float X, float Y)
{
  auto currentPoint = Point(currentX, currentY);
  auto nextPoint = Point(X, Y);
  for (auto& enemy : mEnemies)
  {
    if (enemy->IsAlive() == false)
      continue;

    auto posEnemy = enemy->GetPosition();
    auto enemyPoint = Point(posEnemy.first, posEnemy.second);

    auto nextDist = enemyPoint.getDistance(nextPoint);
    auto currentDist = enemyPoint.getDistance(currentPoint);

    if (nextDist < currentDist && nextDist < mMinDistance)
    {
      return false;
    }
  }

  return true;
}

int EnemiesCollection::GetNumberKilled()
{
  auto killed = 0;
  for (auto& enemy : mEnemies)
  {
    if (enemy->IsAlive() == false)
    {
      killed++;
    }
  }

  return killed;
}

void EnemiesCollection::Update(float delta)
{
  auto heroPos = mHero->GetPosition();
  Vec2 heroPoint = Vec2(heroPos.first, heroPos.second);

  for (auto& enemy : mEnemies)
  {
    enemy->Update(delta);
    
    auto enemyPos = enemy->GetPosition();
    Vec2 enemyPoint = Vec2(enemyPos.first, enemyPos.second);

    auto dist = heroPoint.getDistance(enemyPoint);

    // move
    if (dist > mDistForEnemy)
    {
      int xDirection = 0;
      int yDiretion = 0;

      if (heroPos.first - 20 < enemyPos.first)
      {
        xDirection = -1 * mSpeed;
      }
      if (heroPos.first > enemyPos.first)
      {
        xDirection = mSpeed;
      }

      if (heroPos.second - 20 < enemyPos.second)
      {
        yDiretion = -1 * mSpeed;
      }
      if (heroPos.second > enemyPos.second)
      {
        yDiretion = mSpeed;
      }

      enemy->MoveAt(xDirection, yDiretion);
    }
    else
    {
      if (enemy->GetRegisterDamageAndReset())
      {
        mHero->TakeDamage(10);
      }
      else
      {
        if (mHero->IsAlive())
        {
          enemy->Attack();
        }
      }
    }
  }
}

void EnemiesCollection::SetHero(Hero * aHero)
{
  mHero = aHero;
}
