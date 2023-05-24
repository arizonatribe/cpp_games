#include "actor.h"
#include "bgsprite.h"

BGSprite::BGSprite(Actor* owner, int order) : Sprite(owner, order), scrollSpeed(0.0f) { }

void BGSprite::Update(float deltaTime) {
  Sprite::Update(deltaTime);
  for (auto& bg : bgTextures) {
    bg.offset.x += scrollSpeed * deltaTime;
    if (bg.offset.x < -screenSize.x) {
      bg.offset.x = (bgTextures.size() - 1) * screenSize.x - 1;
    }
  }
}

void BGSprite::SetBGTextures(const std::vector<SDL_Texture*>& bgt) {
  int count = 0;
  for (auto tex : bgt) {
    BGTexture temp;
    temp.texture = tex;
    temp.offset.x = count * screenSize.x;
    temp.offset.y = 0;
    bgTextures.emplace_back(temp);
    count++;
  }
}

void BGSprite::Draw(SDL_Renderer* renderer) {
  for (auto& bg : bgTextures) {
    SDL_Rect r;
    r.w = static_cast<int>(screenSize.x);
    r.h = static_cast<int>(screenSize.y);
    r.x = static_cast<int>(owner->GetPosition().x - r.w / 2 + bg.offset.x);
    r.y = static_cast<int>(owner->GetPosition().y - r.h / 2 + bg.offset.y);
    SDL_RenderCopy(renderer, bg.texture, nullptr, &r);
  }
}
