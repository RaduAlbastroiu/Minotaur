
#include "Updatable.h"
#include "Updater.h"

Updatable::Updatable(Updater* updater)
  :updater(updater)
{
  updater->RegisterUpdatable(this);
}

Updatable::~Updatable()
{
  updater->UnregisterUpdatable(this);
}

void Updatable::Update(float delta)
{
  timePassed += delta;
  DoUpdate(delta);
}
