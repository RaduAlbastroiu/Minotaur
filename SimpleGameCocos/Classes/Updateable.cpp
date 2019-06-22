
#include "Updateable.h"

void Updateable::Update(float delta)
{
  timePassed += delta;
  DoUpdate(delta);
}
