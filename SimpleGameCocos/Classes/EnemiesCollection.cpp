
#include "EnemiesCollection.h"


void EnemiesCollection::AddEnemy(cocos2d::Scene * aScene, float X, float Y)
{
  mEnemies.push_back(make_unique<Enemy>(Enemy(aScene, X, Y)));
}

void EnemiesCollection::AttackAt(float X, float Y, int aForce)
{
  auto heroPoint = Point(X, Y);
  int count = mHitAtOnceMax;
  for (auto& enemy : mEnemies)
  {
    auto posEnemy = enemy->GetPosition();
    auto enemyPoint = Point(posEnemy.first, posEnemy.second);

    auto dist = heroPoint.getDistance(enemyPoint);
    
    if (dist < mDistAttack && count > 0 && enemy->IsAlive())
    {
      enemy->TakeDamage(aForce);
      count--;
    }
  }
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

  // update game mechanics
  mHitAtOnceMax = min(killed / 6 + 1, 5);

  return killed;
}

void EnemiesCollection::Reset()
{
  for (auto& enemy : mEnemies)
  {
    enemy.reset();
  }
  mEnemies.clear();
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

    if (mHero->IsAlive())
    {
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
          enemy->Attack();
        }
      }
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
