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

  Init();
}

void Hero::Init()
{
  SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Minotaur.plist");

  auto label = Label::createWithSystemFont("Health: 100", "Arial", 50);
  label->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
  label->setPosition(Director::getInstance()->getVisibleSize().width / 15, Director::getInstance()->getVisibleSize().height / 1.07);
  label->setTextColor(cocos2d::Color4B::BLACK);

  mHero = Sprite::create("MinotaurFirst.png");
  mHero->setPosition(Vec2(mCurrentPosition.x, mCurrentPosition.y));
  mHero->setScale(3);
  mHero->setAnchorPoint(Vec2(0.5, 0.5));

  mScene->addChild(label, 100);
  mScene->addChild(mHero, 10);

  RunAnimation(mHeroIdle, 1000, mIdleFrecv);
}

void Hero::RunAnimation(vector<string>& aAnimSprites, int aNrRuns, float aFrecv)
{
  auto spritecache = SpriteFrameCache::getInstance();
  Vector<SpriteFrame *> anim;
  for (int i = 0; i < aAnimSprites.size(); i++)
  {
    anim.pushBack(spritecache->getSpriteFrameByName(aAnimSprites[i]));
  }
  auto animation = Animation::createWithSpriteFrames(anim, aFrecv);
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
      RunAnimation(mHeroMove, 1000, mMoveFrecv);
    }
    if (newState == heroState::attack)
    {
      mCurrentState = heroState::attack;
      mHero->stopAction(mLastAction);
      mAttackTimeStart = mTimePassed;
      mEnemiesCollection->AttackAt(mHero->getPositionX(), mHero->getPositionY(), 25);
      RunAnimation(mHeroAttack, 1000, mAttackFrecv);
    }
    if (newState == heroState::dead)
    {
      mCurrentState = heroState::dead;
      mDeadTimeStart = mTimePassed;
      mHero->stopAction(mLastAction);
      RunAnimation(mHeroDead, 1, mDeadFrecv);
    }
  }
  if (mCurrentState == heroState::move)
  {
    if (newState == heroState::idle)
    {
      mCurrentState = heroState::idle;
      mHero->stopAction(mLastAction);
      RunAnimation(mHeroIdle, 1000, mIdleFrecv);
    }
    if (newState == heroState::attack)
    {
      mCurrentState = heroState::attack;
      mHero->stopAction(mLastAction);
      mAttackTimeStart = mTimePassed;
      mEnemiesCollection->AttackAt(mHero->getPositionX(), mHero->getPositionY(), 25);
      RunAnimation(mHeroAttack, 1000, mAttackFrecv);
    }
    if (newState == heroState::dead)
    {
      mCurrentState = heroState::dead;
      mDeadTimeStart = mTimePassed;
      mHero->stopAction(mLastAction);
      RunAnimation(mHeroDead, 1, mDeadFrecv);
    }
  }
  if (mCurrentState == heroState::attack)
  {
    if (newState == heroState::idle)
    {
      mCurrentState = heroState::idle;
      mHero->stopAction(mLastAction);
      RunAnimation(mHeroIdle, 1000, mIdleFrecv);
    }
    if (newState == heroState::move)
    {
      mCurrentState = heroState::move;
      mHero->stopAction(mLastAction);
      RunAnimation(mHeroMove, 1000, mMoveFrecv);
    }
    if (newState == heroState::dead)
    {
      mCurrentState = heroState::dead;
      mDeadTimeStart = mTimePassed;
      mHero->stopAction(mLastAction);
      RunAnimation(mHeroDead, 1, mDeadFrecv);
    }
  }

  if (newState == heroState::hit && mCurrentState != newState)
  {
    mCurrentState = newState;
    mHero->stopAction(mLastAction);
    mHitTimeStart = mTimePassed;
    RunAnimation(mHeroHit, 1, mHitFrecv);
  }
}

void Hero::MovePosition()
{
  auto direction = Vec2(0, 0);
  float X = mHero->getPositionX();
  float Y = mHero->getPositionY();

  if (mDirection == LEFT)
  {
    direction = Vec2(-1 * mSpeed, 0);
    X += -1 * mSpeed;
  }
  if (mDirection == RIGHT)
  {
    direction = Vec2(1 * mSpeed, 0);
    X += mSpeed;
  }
  if (mDirection == UP)
  {
    direction = Vec2(0, 1 * mSpeed);
    Y += mSpeed;
  }
  if (mDirection == DOWN)
  {
    direction = Vec2(0, -1 * mSpeed);
    Y -= mSpeed;
  }
  
  if (mEnemiesCollection->CanMoveAt(mHero->getPositionX(), mHero->getPositionY(), X, Y))
  {
    auto moveBy = MoveBy::create(0.01667f, direction);
    mHero->runAction(moveBy);
  }
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

void Hero::TakeDamage(int damage)
{
  mHealth -= damage;
  mHealth = max(0, mHealth);
  mHealthLabel->setString("Health: " + to_string(mHealth));
  ChangeState(heroState::hit);
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
