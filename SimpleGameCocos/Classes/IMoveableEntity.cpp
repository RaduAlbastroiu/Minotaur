#include "IMoveableEntity.h"

IMoveableEntity::IMoveableEntity(cocos2d::Sprite* aEntity, float aPosX, float aPosY, float aSpeed)
  :mPosX(aPosX), mPosY(aPosY), mSpeed(aSpeed), mEntity(aEntity)
{
  mDirection = MoveDirection::Idle;
  mEntity->setPosition(Vec2(mPosX, mPosY));
}

void IMoveableEntity::SetMoveDirection(int direction)
{
  switch (direction)
  {
  case LEFT:
    mDirection = MoveDirection::Left;
  case RIGHT:
    mDirection = MoveDirection::Right;
  case UP:
    mDirection = MoveDirection::Up;
  case DOWN:
    mDirection = MoveDirection::Down;
  default:
    mDirection = MoveDirection::Idle;
    break;
  }
}

void IMoveableEntity::StopMoving()
{
  mDirection = MoveDirection::Idle;
}

void IMoveableEntity::Update(float delta)
{
  if (mDirection != MoveDirection::Idle)
  {
    cocos2d::Vec2 direction;

    switch (mDirection)
    {
    case IMoveableEntity::MoveDirection::Left:
      direction = Vec2(-1, 0);
      break;
    case IMoveableEntity::MoveDirection::Right:
      direction = Vec2(1, 0);
      break;
    case IMoveableEntity::MoveDirection::Up:
      direction = Vec2(0, 1);
      break;
    case IMoveableEntity::MoveDirection::Down:
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
