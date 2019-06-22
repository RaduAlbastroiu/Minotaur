
#include "Updater.h"
#include "Updatable.h"


void Updater::RegisterUpdatable(Updatable* updateable)
{
  toUpdate.insert(updateable);
}

void Updater::UnregisterUpdatable(Updatable* updateable)
{
  toUpdate.erase(updateable);
}

void Updater::UpdateAll(float delta)
{
  for (auto updateable : toUpdate)
    updateable->Update(delta);
}
