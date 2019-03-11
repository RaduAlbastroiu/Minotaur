#include "Hero.h"

Hero::Hero()
{
}

Hero::Hero(cocos2d::Scene * scene, float positionX, float positionY)
{
  mScene = scene;
  mCurrentPosition.x = positionX;
  mCurrentPosition.y = positionY;
  speed = 10;
  animationDuration = 0.2f;
  lastAnimationTime = 0;
  timePassed = 0;

  mCurrentState = HeroState::stand;

  mCurrentSprite = nullptr;

  for (int i = 0; i < 8; i++)
  {
    auto sprite = GetMinotaurAt(1, i);
    sprite->setScale(5);
    sprite->setAnchorPoint(Vec2(0.5, 0.5));
    mMoveAnimation.push_back(sprite);
  }
  for (int i = 0; i < 9; i++)
  {
    auto sprite = GetMinotaurAt(3, i);
    sprite->setScale(5);
    sprite->setAnchorPoint(Vec2(0.5, 0.5));
    mAttackAnimation.push_back(sprite);
  }
  for (int i = 0; i < 5; i++)
  {
    auto sprite = GetMinotaurAt(0, i);
    sprite->setScale(5);
    sprite->setAnchorPoint(Vec2(0.5, 0.5));
    mStandingAnimation.push_back(sprite);
  }

  ResetCurrentSprite();
}

void Hero::MoveToPosition(float x, float y)
{
}

void Hero::Attack(int type)
{
  // sprite
  auto frames = getAnimation(9);
  aHero = Sprite::createWithSpriteFrame(frames.front());
  this->addChild(aHero);
  aHero->setPosition(500, 500);
  aHero->setScale(5.0);

  AttackAnimation = Animation::createWithSpriteFrames(frames, 0.1, 5);
  cocos2d::Action* action = RepeatForever::create(Animate::create(AttackAnimation));
  aHero->runAction(action);
}

void Hero::Update(float delta)
{
  timePassed += delta;
  if (mCurrentState == HeroState::attack && numberOfRunsAnimation >= 1)
  {
    mCurrentState = HeroState::stand;
  }

  if (timePassed - lastAnimationTime > animationDuration)
  {
    position pos;
    pos.x = 500;
    pos.y = 300;
    switch (mCurrentState)
    {
    case Hero::attack:
      DrawNextAttackAnimation(pos);
      break;
    case Hero::move:
      DrawNextMoveAnimation(pos);
      break;
    case Hero::stand:
      DrawNextStandingAnimation(pos);
      break;
    default:
      break;
    }
  }
}

void Hero::ResetCurrentSprite()
{
  mCurrentMoveSprite = 0;
  mCurrentAttackSprite = 0;
  mCurrentStangindSprite = 0;
}

void Hero::DrawNextMoveAnimation(position aPosition)
{
  if (mCurrentMoveSprite == mMoveAnimation.size())
  {
    mCurrentMoveSprite = 0;
  }

  if (mCurrentSprite != nullptr)
  {
    mCurrentSprite->removeFromParent();
  }
  mCurrentSprite = mMoveAnimation[mCurrentMoveSprite];
  mCurrentSprite->setPosition(Vec2(aPosition.x, aPosition.y));
  mScene->addChild(mCurrentSprite);

  mCurrentMoveSprite++;
  if (mCurrentMoveSprite == mMoveAnimation.size())
  {
    numberOfRunsAnimation++;
  }
}

void Hero::DrawNextAttackAnimation(position aPosition)
{
  if (mCurrentAttackSprite == mAttackAnimation.size())
  {
    mCurrentAttackSprite = 0;
  }

  if (mCurrentSprite != nullptr)
  {
    mCurrentSprite->removeFromParent();
  }
  mCurrentSprite = mAttackAnimation[mCurrentAttackSprite];
  mCurrentSprite->setPosition(Vec2(aPosition.x, aPosition.y));
  mScene->addChild(mCurrentSprite);

  mCurrentAttackSprite++;
  if (mCurrentAttackSprite == mAttackAnimation.size())
  {
    numberOfRunsAnimation++;
  }
}

void Hero::DrawNextStandingAnimation(position aPosition)
{
  if (mCurrentStangindSprite == mStandingAnimation.size())
  {
    mCurrentStangindSprite = 0;
  }

  if (mCurrentSprite != nullptr)
  {
    mCurrentSprite->removeFromParent();
  }
  mCurrentSprite = mStandingAnimation[mCurrentStangindSprite];
  mCurrentSprite->setPosition(Vec2(aPosition.x, aPosition.y));
  mScene->addChild(mCurrentSprite);

  mCurrentStangindSprite++;
  if (mCurrentStangindSprite == mStandingAnimation.size())
  {
    numberOfRunsAnimation++;
  }
}

cocos2d::Sprite * Hero::GetMinotaurAt(int x, int y)
{
  int X = x * 96;
  int Y = y * 96;

  cocos2d::Sprite* sprite = Sprite::create("Minotaur.png", Rect(Y, X, 96, 96));
  return sprite;
}
