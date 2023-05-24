#ifndef BGSPRITE_H
#define BGSPRITE_H

#include "math.h"
#include "sprite.h"
#include <vector>

class BGSprite : public Sprite {
  public:
    BGSprite(class Actor* ownr, int drawOrder = 10);

    void Update(float deltaTime) override;
    void Draw(SDL_Renderer* renderer) override;

    void SetBGTextures(const std::vector<SDL_Texture*>& bgt);
    void SetScreenSize(const Vector2& s) { screenSize = s; }
    void SetScrollSpeed(float s) { scrollSpeed = s; }
    float GetScrollSpeed() const { return scrollSpeed; }

  private:
    struct BGTexture {
      SDL_Texture* texture;
      Vector2 offset;
    };

    std::vector<BGTexture> bgTextures;
    Vector2 screenSize;
    float scrollSpeed;
};

#endif
