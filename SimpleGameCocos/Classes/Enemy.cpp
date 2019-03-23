#include "Enemy.h"


Enemy::Enemy(cocos2d::Scene * scene, Hero * aHero, float X, float Y)
{
  mScene = scene;
  mHero = aHero;

  mCurrentPosition.x = X;
  mCurrentPosition.y = Y;
  mDirection = NODIRECTION;
  mCurrentState = enemyState::idle;

  mEnemy = Sprite::create("Skeleton/Skeleton.png");
  mEnemy->setPosition(Vec2(mCurrentPosition.x, mCurrentPosition.y));
  mEnemy->setScale(3);
  mEnemy->setAnchorPoint(Vec2(0.5, 0.5));

  scene->addChild(mEnemy);

  Init();
}

void Enemy::TakeDamage(float damage)
{
  mHealth -= damage;
}

void Enemy::Update(float delta)
{
  mTimePassed += delta;
}

void Enemy::Init()
{
}

void Enemy::RunIdleAnimation()
{
}
