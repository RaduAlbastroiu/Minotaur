#include "Hero.h"

Hero::Hero()
{
  Init();
}

Hero::Hero(cocos2d::Scene * scene, float positionX, float positionY)
{
  mScene = scene;
  mCurrentPosition.x = positionX;
  mCurrentPosition.y = positionY;

  mHero = Sprite::create("MinotaurFirst.png");
  mHero->setPosition(Vec2(mCurrentPosition.x, mCurrentPosition.y));
  mHero->setScale(5);

  Init();
}

void Hero::Init()
{
  SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Minotaur.plist");

  mCurrentState = heroState::idle;
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
  mHero->runAction(action);
}

void Hero::MoveToPosition(float x, float y)
{
}

void Hero::Attack(int type)
{
}

void Hero::Update(float delta)
{
  mTimePassed += delta;
}

void Hero::Move(int direction, float delta)
{
  if (mCurrentState != move)
  {
    mCurrentState = move;
    RunMoveAnimation();
  }

  switch (direction)
  {
  case 1:
    // left
    break;
  case 2:
    // right
    break;
  case 3:
    // up
    break;
  case 4:
    // down
    break;
  default:
    mCurrentState = idle;
    RunIdleAnimation();
    break;
  }
}
