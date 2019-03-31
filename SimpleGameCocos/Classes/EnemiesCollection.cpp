#pragma once

#include "EnemiesCollection.h"


void EnemiesCollection::AddEnemy(cocos2d::Scene * aScene, float X, float Y)
{
  mEnemies.push_back(make_unique<Enemy>(Enemy(aScene, X, Y)));
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
      enemy->TakeDamage(aForce);
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

    if (dist > mDistForEnemy && enemy->GetState() != enemyState::dead && enemy->GetState() != enemyState::hit)
    {
      enemy->ChangeState(enemyState::move);
      auto enemySprite = enemy->GetSprite();
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

      auto moveBy = MoveBy::create(0.01667f, Vec2(xDirection, yDiretion));
      enemySprite->runAction(moveBy);
    }
    else
    {
      enemy->ChangeState(enemyState::idle);
    }
  }
}

void EnemiesCollection::SetHero(Hero * aHero)
{
  mHero = aHero;
}
