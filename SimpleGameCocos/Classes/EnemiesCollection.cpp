
#include "EnemiesCollection.h"


void EnemiesCollection::AddEnemy(cocos2d::Scene * aScene, float X, float Y)
{
  mEnemies.push_back(make_unique<Enemy>(Enemy(aScene, X, Y)));
}

void EnemiesCollection::AttackCollection()
{
  auto pos = mHero->GetPosition();
  auto heroPoint = Point(pos.first, pos.second);
  int count = mHitAtOnceMax;
  for (auto& enemy : mEnemies)
  {
    auto posEnemy = enemy->GetPosition();
    auto enemyPoint = Point(posEnemy.first, posEnemy.second);

    auto dist = heroPoint.getDistance(enemyPoint);
    
    if (dist < 175 && count > 0 && enemy->IsAlive())
    {
      enemy->TakeDamage(HERO_STRENGTH);
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
  mEnemies.clear();
}

void EnemiesCollection::Update(float delta)
{
  auto heroPos = mHero->GetPosition();
  Vec2 heroPoint = Vec2(heroPos.first, heroPos.second);

  // set action for each enemy
  for (auto& enemy : mEnemies)
  {
    // update enemy
    enemy->DoUpdate(delta);

    // get enemy position
    auto enemyPos = enemy->GetPosition();
    Vec2 enemyPoint = Vec2(enemyPos.first, enemyPos.second);

    // distance to target
    auto dist = heroPoint.getDistance(enemyPoint);

    // if target alive
    if (mHero->IsAlive())
    {
      // if not in range for attack
      if (dist > 125)
      {
        int xDirection = 0;
        int yDiretion = 0;

        if (heroPos.first - 20 < enemyPos.first)
        {
          xDirection = -2;
        }
        if (heroPos.first > enemyPos.first)
        {
          xDirection = 2;
        }

        if (heroPos.second - 20 < enemyPos.second)
        {
          yDiretion = -2;
        }
        if (heroPos.second > enemyPos.second)
        {
          yDiretion = 2;
        }

        // move towards target
        enemy->MoveAt(xDirection, yDiretion);
      }
      // if in range for attack
      else
      {
        // if the enemy provoked damage to the target
        if (enemy->DidFinishAttack())
        {
          mHero->TakeDamage(10);
        }
        // try provoke damage
        else
        {
          enemy->Attack();
        }
      }
    }
    // if target dead
    else
    {
      enemy->Idle();
    }
  }
}

void EnemiesCollection::SetHero(Hero * aHero)
{
  mHero = aHero;
}
