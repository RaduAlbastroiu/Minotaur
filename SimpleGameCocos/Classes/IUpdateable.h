#pragma once

#pragma once

#include "cocos2d.h"
#include "Includes.h"


class IUpdateable
{
public:

  virtual void Update(float delta) = 0;

private:

  float timePassed = 0;
};
