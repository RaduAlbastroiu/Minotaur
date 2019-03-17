#pragma once

#include <vector>
#include "cocos2d.h"

#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4

USING_NS_CC;
using namespace std;

class IMoveableEntity
{
public:
  IMoveableEntity(cocos2d::Sprite* aEntity, float aPosX, float aPosY, float aSpeed);

  void SetMoveDirection(int direction);
  void StopMoving();

  void Update(float delta);

protected:

  enum class MoveDirection{
    Left,
    Right,
    Up,
    Down,
    Idle
  };

  MoveDirection mDirection;

  float mPosX;
  float mPosY;
  float mSpeed;

  cocos2d::Sprite* mEntity;

};

