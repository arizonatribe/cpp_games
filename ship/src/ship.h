#ifndef SHIP_H
#define SHIP_H

#include "actor.h"
#include <cstdint>

class Ship : public Actor {
  public:
    Ship(class Game* game);

    void UpdateActor(float deltaTime) override;
    void ProcessKeyboard(const uint8_t* state);

    float GetRightSpeed() const { return rightSpeed; };
    float GetDownSpeed() const { return downSpeed; };

  private:
    float rightSpeed;
    float downSpeed;
};

#endif
