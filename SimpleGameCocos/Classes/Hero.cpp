#include "Hero.h"

Hero::Hero(cocos2d::Scene * scene)
{
  mScene = scene;

  mCurrentPosition.x = Director::getInstance()->getVisibleSize().width / 2;
  mCurrentPosition.y = Director::getInstance()->getVisibleSize().height / 2;
  mDirection = NODIRECTION;
  mCurrentState = heroState::idle;

  mHero = Sprite::create("MinotaurFirst.png");
  mHero->setPosition(Vec2(mCurrentPosition.x, mCurrentPosition.y));
  mHero->setScale(5);

  Init();
}

void Hero::Init()
{
  // Add sprites
  SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Minotaur.plist");
  RunIdleAnimation();
  mScene->addChild(mHero);
}

void Hero::RunIdleAnimation()
{
  auto spritecache = SpriteFrameCache::getInstance();
  Vector<SpriteFrame *> animIdle;
  for (int i = 0; i < 5; i++)
  {
    animIdle.pushBack(spritecache->getSpriteFrameByName(mHeroIdle[i]));
  }
  auto idleAnimation = Animation::createWithSpriteFrames(animIdle, 0.2);
  cocos2d::Action* action = RepeatForever::create(Animate::create(idleAnimation));
  mLastAction = action;
  mHero->runAction(action);
}

void Hero::RunMoveAnimation()
{
  auto spritecache = SpriteFrameCache::getInstance();
  Vector<SpriteFrame *> animMove;
  for (int i = 0; i < 8; i++)
  {
    animMove.pushBack(spritecache->getSpriteFrameByName(mHeroMove[i]));
  }
  auto moveAnimation = Animation::createWithSpriteFrames(animMove, 0.1);
  cocos2d::Action* action = RepeatForever::create(Animate::create(moveAnimation));
  mLastAction = action;
  mHero->runAction(action);
}


void Hero::RunAttackAnimation()
{
  auto spritecache = SpriteFrameCache::getInstance();
  Vector<SpriteFrame *> attackAnim;
  for (int i = 0; i < 8; i++)
  {
    attackAnim.pushBack(spritecache->getSpriteFrameByName(mHeroAttack[i]));
  }
  auto attackAnimation = Animation::createWithSpriteFrames(attackAnim, 0.1);
  cocos2d::Action* action = RepeatForever::create(Animate::create(attackAnimation));
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
      RunMoveAnimation();
    }
    if (newState == heroState::attack)
    {
      mCurrentState = heroState::attack;
      mHero->stopAction(mLastAction);
      mAttackTimeStart = mTimePassed;
      RunAttackAnimation();
    }
  }
  if (mCurrentState == heroState::move)
  {
    if (newState == heroState::idle)
    {
      mCurrentState = heroState::idle;
      mHero->stopAction(mLastAction);
      RunIdleAnimation();
    }
    if (newState == heroState::attack)
    {
      mCurrentState = heroState::attack;
      mHero->stopAction(mLastAction);
      mAttackTimeStart = mTimePassed;
      RunAttackAnimation();
    }
  }
  if (mCurrentState == heroState::attack)
  {
    if (newState == heroState::idle)
    {
      mCurrentState = heroState::idle;
      mHero->stopAction(mLastAction);
      RunIdleAnimation();
    }
    if (newState == heroState::move)
    {
      mCurrentState = heroState::move;
      mHero->stopAction(mLastAction);
      RunMoveAnimation();
    }
  }
}

void Hero::Attack()
{
  mAttackTimeStart = mTimePassed;
  ChangeState(heroState::attack);
}

void Hero::SetMoveDirection(int direction)
{
  mDirection = direction;
}

void Hero::Update(float delta)
{
  mTimePassed += delta;

  // change direction
  if (mDirection == LEFT)
    mHero->setFlippedX(true);
  if (mDirection == RIGHT)
    mHero->setFlippedX(false);

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
  if (mCurrentState == heroState::attack && mTimePassed - mAttackTimeStart > 0.5f)
  {
    ChangeState(heroState::idle);
  }
}
