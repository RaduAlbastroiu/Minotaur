#pragma once

#include "Includes.h"

class KeyboardListener : public cocos2d::Node
{
public:
  EventListenerKeyboard* initKeyboard();
  int GetMoveDirection();
  bool GetAttackStatus();
  bool IsKeyboardPresed();

private:
  
  map<EventKeyboard::KeyCode, bool> mKeyboard;
};
