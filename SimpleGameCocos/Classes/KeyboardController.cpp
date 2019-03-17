#include "KeyboardController.h"


void KeyboardController::Init(Hero* aHero)
{
  mHero = aHero;

  auto listener = EventListenerKeyboard::create();
  listener->onKeyPressed = CC_CALLBACK_2(KeyboardController::onKeyPressed, this);
  listener->onKeyReleased = CC_CALLBACK_2(KeyboardController::onKeyReleased, this);

  Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void KeyboardController::Update(float delta)
{
  if (mDirection < 0)
  {
    // mHero->StopMoving;
    mDirection = 0;
  }
  else
  {
    // mHero->Move(delta);
  }
}

bool KeyboardController::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
  switch (keyCode) {
  case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
  case EventKeyboard::KeyCode::KEY_A:
    mDirection = LEFT;
    break;
  case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
  case EventKeyboard::KeyCode::KEY_D:
    mDirection = RIGHT;
    break;
  case EventKeyboard::KeyCode::KEY_UP_ARROW:
  case EventKeyboard::KeyCode::KEY_W:
    mDirection = UP;
    break;
  case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
  case EventKeyboard::KeyCode::KEY_S:
    mDirection = DOWN;
    break;
  default:
    break;
  }

  return true;
}

bool KeyboardController::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
  switch (keyCode) {
  case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
  case EventKeyboard::KeyCode::KEY_A:
    mDirection = -1;
    break;
  case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
  case EventKeyboard::KeyCode::KEY_D:
    mDirection = -1;
    break;
  case EventKeyboard::KeyCode::KEY_UP_ARROW:
  case EventKeyboard::KeyCode::KEY_W:
    mDirection = -1;
    break;
  case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
  case EventKeyboard::KeyCode::KEY_S:
    mDirection = -1;
    break;
  default:
    break;
  }

  return true;
}
