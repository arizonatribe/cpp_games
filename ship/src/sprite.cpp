#include "actor.h"
#include "game.h"
#include "sprite.h"

Sprite::Sprite(Actor* ownr, int order)
  :Component(ownr)
  , texture(nullptr)
  , drawOrder(order)
  , textureWidth(0)
  , textureHeight(0)
{
  owner->GetGame()->AddSprite(this);
}

Sprite::~Sprite() {
  owner->GetGame()->RemoveSprite(this);
}

void Sprite::Draw(SDL_Renderer* renderer) {
  if (texture) {
    SDL_Rect r;
    r.w = static_cast<int>(textureWidth * owner->GetScale());
    r.h = static_cast<int>(textureHeight * owner->GetScale());
    r.x = static_cast<int>(owner->GetPosition().x - r.w / 2);
    r.y = static_cast<int>(owner->GetPosition().y - r.h / 2);

    SDL_RenderCopyEx(
      renderer,
      texture,
      nullptr,
      &r,
      -Math::ToDegrees(owner->GetRotation()),
      nullptr,
      SDL_FLIP_NONE
    );
  }
}

void Sprite::SetTexture(SDL_Texture* text) {
  texture = text;
  SDL_QueryTexture(text, nullptr, nullptr, &textureWidth, &textureHeight);
}
