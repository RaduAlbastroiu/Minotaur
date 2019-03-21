#include "Hero.h"

Hero::Hero(cocos2d::Scene * scene, float positionX, float positionY)
{
  mScene = scene;
  mCurrentPosition.x = positionX;
  mCurrentPosition.y = positionY;
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
  mIdleAction = action;
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
  mMoveAction = action;
  mHero->runAction(action);
}

void Hero::RunAttackAnimation()
{
  auto spritecache = SpriteFrameCache::getInstance();
  Vector<SpriteFrame *> attackAnim;
  for (int i = 0; i < 8; i++)
  {
    attackAnim.pushBack(spritecache->getSpriteFrameByName(mHeroMove[i]));
  }
  auto attackAnimation = Animation::createWithSpriteFrames(attackAnim, 0.1);
  cocos2d::Action* action = RepeatForever::create(Animate::create(attackAnimation));
  mAttackAction = action;
  mHero->runAction(action);
}

void Hero::Attack()
{
}

void Hero::SetMoveDirection(int direction)
{
  mDirection = direction;
}

void Hero::Update(float delta)
{
  mTimePassed += delta;

  if (mDirection != NODIRECTION && mCurrentState != heroState::move)
  {
    mCurrentState = heroState::move;
    mHero->stopAction(mIdleAction);
    RunMoveAnimation();
  }

  if (mDirection == NODIRECTION && mCurrentState == heroState::move)
  {
    mCurrentState = heroState::idle;
    mHero->stopAction(mMoveAction);
    RunIdleAnimation();
  }

}
