#include "actor.h"
#include "game.h"
#include "component.h"
#include <algorithm>

Actor::Actor(Game* g)
  :game(g)
  , state(State::Active)
  , scale(1.0f)
  , rotation(1.0f)
  , position(Vector2::Zero)
{
  game->AddActor(this);
}

Actor::~Actor() {
  game->RemoveActor(this);

  while (!components.empty()) {
    delete components.back();
  }
}

void Actor::Update(float deltaTime) {
  if (state == Active) {
    UpdateComponents(deltaTime);
    UpdateActor(deltaTime);
  }
}

void Actor::UpdateActor(float deltaTime) {}

void Actor::UpdateComponents(float deltaTime) {
  for (auto c : components) {
    c->Update(deltaTime);
  }
}

void Actor::AddComponent(Component* component)
{
  int order = component->GetUpdateOrder();
  auto iter = components.begin();

  for (; iter != components.end(); ++iter) {
    if (order < (*iter)->GetUpdateOrder()) {
      break;
    }
  }

  components.insert(iter, component);
}

void Actor::RemoveComponent(Component* component)
{
  auto iter = std::find(components.begin(), components.end(), component);
  if (iter != components.end()) {
    components.erase(iter);
  }
}
