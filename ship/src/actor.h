#ifndef ACTOR_H
#define ACTOR_H

#include "math.h"
#include <vector>

class Actor {
  public:
    enum State { Active, Paused, Dead };

    Actor(class Game* g);
    virtual ~Actor();

    void Update(float deltaTime);
    void UpdateComponents(float deltaTime);
    virtual void UpdateActor(float deltaTime);

    const Vector2& GetPosition() const { return position; }
    void SetPosition(const Vector2& pos) { position = pos; }

    float GetRotation() const { return rotation; }
    void SetRotation(float r) { rotation = r; }

    float GetScale() const { return scale; }
    void SetScale(float s) { scale = s; }

    State GetState() const { return state; }
    void SetState(State st) { state = st; }

    class Game* GetGame() { return game; }

    void AddComponent(class Component* component);
    void RemoveComponent(class Component* component);

  private:
    State state;
    float scale;
    float rotation;
    Vector2 position;

    class Game* game;
    std::vector<class Component*> components;
};

#endif
