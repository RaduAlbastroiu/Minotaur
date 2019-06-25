
#include "KeyboardListener.h"


KeyboardListener::KeyboardListener()
{
  listener = EventListenerKeyboard::create();

  listener->onKeyPressed = [&](cocos2d::EventKeyboard::KeyCode keycode, Event* event) {
    mKeyboard[keycode] = true;
  };

  listener->onKeyReleased = [&](cocos2d::EventKeyboard::KeyCode keycode, Event* event) {
    mKeyboard.erase(keycode);
  };

}

EventListenerKeyboard* KeyboardListener::GetListener()
{
  return listener;
}

int KeyboardListener::GetMoveDirection()
{
  for (auto keyPressed : mKeyboard)
  {
    auto keyCode = keyPressed.first;

    switch (keyCode) {
    case EventKeyboard::KeyCode::KEY_A:
      return LEFT;
    case EventKeyboard::KeyCode::KEY_D:
      return RIGHT;
    case EventKeyboard::KeyCode::KEY_W:
      return UP;
    case EventKeyboard::KeyCode::KEY_S:
      return DOWN;
    }
  } 
  return NODIRECTION;
}

bool KeyboardListener::GetAttackStatus()
{
  if (mKeyboard.find(EventKeyboard::KeyCode::KEY_SPACE) != mKeyboard.end())
  {
    return true;
  }

  return false;
}

bool KeyboardListener::IsKeyboardPresed()
{
  for (auto keyPressed : mKeyboard)
  {
    if (keyPressed.second == true)
    {
      return true;
    }
  }
  return false;
}
