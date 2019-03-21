#include "KeyboardController.h"


void KeyboardController::Init(Hero* aHero)
{
  mHero = aHero;

  
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
