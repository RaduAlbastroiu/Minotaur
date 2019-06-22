#pragma once

#include "cocos2d.h"
#include "Includes.h"

class Updater;

class Updatable
{
public:
  Updatable(Updater* updater);
  ~Updatable();

  void Update(float delta);

protected:
  virtual void DoUpdate(float delta) = 0;
  float timePassed = 0;

  Updater* updater;
};
