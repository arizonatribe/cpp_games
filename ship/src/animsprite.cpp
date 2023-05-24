#include "animsprite.h"
#include "math.h"

AnimSprite::AnimSprite(Actor* owner, int drawOrder)
  : Sprite(owner, drawOrder)
  , animFPS(24.0f)
  , currFrame(0.0f)
{
}

void AnimSprite::Update(float deltaTime) {
  Sprite::Update(deltaTime);

  if (animTextures.size() > 0) {
    currFrame += animFPS * deltaTime;
    while (currFrame >= animTextures.size()) {
      currFrame -= animTextures.size();
    }

    SetTexture(animTextures[static_cast<int>(currFrame)]);
  }
}

void AnimSprite::SetAnimTextures(const std::vector<SDL_Texture*>& textures) {
  animTextures = textures;
  if (animTextures.size() > 0) {
    currFrame = 0.0f;
    SetTexture(animTextures[0]);
  }
}
