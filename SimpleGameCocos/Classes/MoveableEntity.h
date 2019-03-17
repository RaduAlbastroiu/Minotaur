#pragma once

#include "cocos2d.h"
#include "Direction.h"

USING_NS_CC;
using namespace std;

class MoveableEntity
{
public:
  MoveableEntity(cocos2d::Sprite* aEntity, float aPosX, float aPosY, float aSpeed);

  void SetMoveDirection(Direction direction);
  void StopMoving();

  void Update(float delta);

protected:

  Direction mDirection;

  float mPosX;
  float mPosY;
  float mSpeed;

  cocos2d::Sprite* mEntity;

};

