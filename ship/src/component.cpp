#include "component.h"
#include "actor.h"

Component::Component(Actor* ownr, int order) : owner(ownr), updateOrder(order) {
  owner->AddComponent(this);
}

Component::~Component() {
  owner->RemoveComponent(this);
}
void Component::Update(float deltaTime) { }
