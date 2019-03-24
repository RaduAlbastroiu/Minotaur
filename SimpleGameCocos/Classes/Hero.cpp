#include "Hero.h"
#include "EnemiesCollection.h"

Hero::Hero(cocos2d::Scene * scene, EnemiesCollection* aEnemiesCollection)
{
  mScene = scene;
  mEnemiesCollection = aEnemiesCollection;

  mCurrentPosition.x = Director::getInstance()->getVisibleSize().width / 2;
  mCurrentPosition.y = Director::getInstance()->getVisibleSize().height / 2;
  mDirection = NODIRECTION;
  mCurrentState = heroState::idle;

  mHero = Sprite::create("MinotaurFirst.png");
  mHero->setPosition(Vec2(mCurrentPosition.x, mCurrentPosition.y));
  mHero->setScale(3);
  mHero->setAnchorPoint(Vec2(0.5, 0.5));

  Init();
}

void Hero::Init()
{
  // Add sprites
  SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Minotaur.plist");
  RunAnimation(mHeroIdle, 1000);
  mScene->addChild(mHero, 100);
}

void Hero::RunAnimation(vector<string>& aAnimSprites, int aNrRuns)
{
  auto spritecache = SpriteFrameCache::getInstance();
  Vector<SpriteFrame *> anim;
  for (int i = 0; i < aAnimSprites.size(); i++)
  {
    anim.pushBack(spritecache->getSpriteFrameByName(aAnimSprites[i]));
  }
  auto animation = Animation::createWithSpriteFrames(anim, 0.1);
  cocos2d::Action* action = Repeat::create(Animate::create(animation), aNrRuns);
  mLastAction = action;
  mHero->runAction(action);
}

void Hero::ChangeState(heroState newState)
{
  if (mCurrentState == heroState::idle)
  {
    if (newState == heroState::move)
    {
      mCurrentState = heroState::move;
      mHero->stopAction(mLastAction);
      RunAnimation(mHeroMove, 1000);
    }
    if (newState == heroState::attack)
    {
      mCurrentState = heroState::attack;
      mHero->stopAction(mLastAction);
      mAttackTimeStart = mTimePassed;
      mEnemiesCollection->AttackAt(mHero->getPositionX(), mHero->getPositionY(), 25);
      RunAnimation(mHeroAttack, 1000);
    }
    if (newState == heroState::dead)
    {
      mCurrentState = heroState::dead;
      mDeadTimeStart = mTimePassed;
      mHero->stopAction(mLastAction);
      RunAnimation(mHeroDead, 1);
    }
  }
  if (mCurrentState == heroState::move)
  {
    if (newState == heroState::idle)
    {
      mCurrentState = heroState::idle;
      mHero->stopAction(mLastAction);
      RunAnimation(mHeroIdle, 1000);
    }
    if (newState == heroState::attack)
    {
      mCurrentState = heroState::attack;
      mHero->stopAction(mLastAction);
      mAttackTimeStart = mTimePassed;
      mEnemiesCollection->AttackAt(mHero->getPositionX(), mHero->getPositionY(), 25);
      RunAnimation(mHeroAttack, 1000);
    }
    if (newState == heroState::dead)
    {
      mCurrentState = heroState::dead;
      mDeadTimeStart = mTimePassed;
      mHero->stopAction(mLastAction);
      RunAnimation(mHeroDead, 1);
    }
  }
  if (mCurrentState == heroState::attack)
  {
    if (newState == heroState::idle)
    {
      mCurrentState = heroState::idle;
      mHero->stopAction(mLastAction);
      RunAnimation(mHeroIdle, 1000);
    }
    if (newState == heroState::move)
    {
      mCurrentState = heroState::move;
      mHero->stopAction(mLastAction);
      RunAnimation(mHeroMove, 1000);
    }
    if (newState == heroState::dead)
    {
      mCurrentState = heroState::dead;
      mDeadTimeStart = mTimePassed;
      mHero->stopAction(mLastAction);
      RunAnimation(mHeroDead, 1);
    }
  }
}

void Hero::MovePosition()
{
  auto direction = Vec2(0, 0);
  if (mDirection == LEFT)
  {
   direction = Vec2(-1 * mSpeed, 0);
  }
  if (mDirection == RIGHT)
  {
    direction = Vec2(1 * mSpeed, 0);
  }
  if (mDirection == UP)
  {
    direction = Vec2(0, 1 * mSpeed);
  }
  if (mDirection == DOWN)
  {
    direction = Vec2(0, -1 * mSpeed);
  }

  auto moveBy = MoveBy::create(0.01667f, direction);
  mHero->runAction(moveBy);
}

void Hero::Attack()
{
  mAttackTimeStart = mTimePassed;
  if (mCurrentState != heroState::attack)
  {
    ChangeState(heroState::attack);
  }
}

void Hero::SetMoveDirection(int direction)
{
  mDirection = direction;
}

void Hero::TakeDamage(float damage)
{
  mHealth -= damage;
}


void Hero::Update(float delta)
{
  mTimePassed += delta;

  // change direction
  if (mDirection == LEFT)
    mHero->setFlippedX(true);
  if (mDirection == RIGHT)
    mHero->setFlippedX(false);

  // change position relative to framerate
  if (mCurrentState == heroState::move)
  {
    MovePosition();
  }

  // change between walking and idling
  if (mDirection != NODIRECTION && mCurrentState == heroState::idle)
  {
    ChangeState(heroState::move);
  }

  if (mDirection == NODIRECTION && mCurrentState == heroState::move)
  {
    ChangeState(heroState::idle);
  }

  // change between attack and idle
  if (mCurrentState == heroState::attack && mTimePassed - mAttackTimeStart > 0.175f)
  {
    ChangeState(heroState::idle);
  }

  // update health 
  if (mHealth <= 0 && mCurrentState != heroState::dead)
  {
    ChangeState(heroState::dead);
  }
}
