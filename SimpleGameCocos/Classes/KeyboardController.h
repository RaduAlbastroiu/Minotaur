#pragma once

#include <vector>
#include "cocos2d.h"
#include "Hero.h"

#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4

USING_NS_CC;
using namespace std;

class KeyboardController : public cocos2d::Node
{
public:

  void Init(Hero* aHero);
  void Update(float delta);

private:

  bool onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
  bool onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

  int mDirection;

  Hero* mHero;
};

