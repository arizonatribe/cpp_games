#ifndef ANIMSPRITE_H
#define ANIMSPRITE_H

#include "sprite.h"
#include <vector>

class AnimSprite : public Sprite {
  public:
    AnimSprite(class Actor* owner, int drawOrder = 100);

    void Update(float deltaTime) override;

    void SetAnimTextures(const std::vector<SDL_Texture*>& textures);
    float GetAnimFPS() const { return animFPS; }
    void SetAnimFPS(float a) { animFPS = a; }

  private:
    float currFrame;
    float animFPS;
    std::vector<SDL_Texture*> animTextures;

};

#endif
