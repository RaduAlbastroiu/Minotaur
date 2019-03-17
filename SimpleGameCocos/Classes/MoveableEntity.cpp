#include "MoveableEntity.h"

MoveableEntity::MoveableEntity(cocos2d::Sprite* aEntity, float aPosX, float aPosY, float aSpeed)
  :mPosX(aPosX), mPosY(aPosY), mSpeed(aSpeed), mEntity(aEntity)
{
  mDirection = Direction::Idle;
  mEntity->setPosition(Vec2(mPosX, mPosY));
}

void MoveableEntity::SetMoveDirection(Direction direction)
{
  switch (direction)
  {
  case Direction::Left :
    mDirection = Direction::Left;
    break;
  case Direction::Right:
    mDirection = Direction::Right;
    break;
  case Direction::Up:
    mDirection = Direction::Up;
    break;
  case Direction::Down:
    mDirection = Direction::Down;
    break;
  default:
    break;
  }
}

void MoveableEntity::StopMoving()
{
  mDirection = Direction::Idle;
}

void MoveableEntity::Update(float delta)
{
  if (mDirection != Direction::Idle)
  {
    cocos2d::Vec2 direction;

    switch (mDirection)
    {
    case Direction::Left:
      direction = Vec2(-1, 0);
      break;
    case Direction::Right:
      direction = Vec2(1, 0);
      break;
    case Direction::Up:
      direction = Vec2(0, 1);
      break;
    case Direction::Down:
      direction = Vec2(0, -1);
      break;
    default:
      break;
    }

    cocos2d::Vec2 computedDirection = (direction * mSpeed) / delta;

    cocos2d::Action* moveAction = cocos2d::MoveBy::create(delta, computedDirection);
    mEntity->runAction(moveAction);
  }
}
