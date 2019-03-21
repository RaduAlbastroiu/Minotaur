#pragma once

#include <vector>
#include "cocos2d.h"
#include "Hero.h"

USING_NS_CC;
using namespace std;

class KeyboardController : public cocos2d::Node
{
public:

  void Init(Hero* aHero);
  void Update(float delta);

private:

  int mDirection;

  Hero* mHero;
};

