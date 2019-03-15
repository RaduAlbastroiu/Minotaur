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

  InitIdleAnimation();
  InitMoveAnimation();
  InitAttackAnimation();

  mScene->addChild(mHero);
}

void Hero::InitIdleAnimation()
{
  auto spritecache = SpriteFrameCache::getInstance();
  Vector<SpriteFrame *> animIdle;
  for (int i = 0; i < 5; i++)
  {
    animIdle.pushBack(spritecache->getSpriteFrameByName(mHeroIdle[i]));
  }
  mIdleAnimation = Animation::createWithSpriteFrames(animIdle, 0.2);
}

void Hero::InitMoveAnimation()
{
  auto spritecache = SpriteFrameCache::getInstance();
  Vector<SpriteFrame *> animMove;
  for (int i = 0; i < 8; i++)
  {
    animMove.pushBack(spritecache->getSpriteFrameByName(mHeroMove[i]));
  }
  mMoveAnimation = Animation::createWithSpriteFrames(animMove, 0.1);
}

void Hero::InitAttackAnimation()
{
  auto spritecache = SpriteFrameCache::getInstance();
  Vector<SpriteFrame *> attackAnim;
  for (int i = 0; i < 8; i++)
  {
    attackAnim.pushBack(spritecache->getSpriteFrameByName(mHeroMove[i]));
  }
  mAttackAnimation = Animation::createWithSpriteFrames(attackAnim, 0.1);
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

  if (mTimePassed > 3 && started == false)
  {
    auto spritecache = SpriteFrameCache::getInstance();
    Vector<SpriteFrame *> animMove;
    for (int i = 0; i < 8; i++)
    {
      animMove.pushBack(spritecache->getSpriteFrameByName(mHeroMove[i]));
    }
    mMoveAnimation = Animation::createWithSpriteFrames(animMove, 0.1);

    cocos2d::Action* action = RepeatForever::create(Animate::create(mMoveAnimation));
    mHero->runAction(action);
    cocos2d::Action* action2 = cocos2d::MoveBy::create(7, cocos2d::Vec2(2500, 0));
    mHero->runAction(action2);
    started = true;
  }
  
}
