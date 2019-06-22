#pragma once

#pragma once

#include "cocos2d.h"
#include "Includes.h"


class Updateable
{
public:
  void Update(float delta);

protected:
  virtual void DoUpdate(float delta) = 0;
  float timePassed = 0;
};
