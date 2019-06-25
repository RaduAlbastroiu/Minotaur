#pragma once

#include "Includes.h"

class KeyboardListener : public cocos2d::Node
{
public:
  KeyboardListener();
  EventListenerKeyboard* GetListener();

  int GetMoveDirection();
  bool GetAttackStatus();
  bool IsKeyboardPresed();

private:
  
  EventListenerKeyboard* listener;
  map<EventKeyboard::KeyCode, bool> mKeyboard;
};
