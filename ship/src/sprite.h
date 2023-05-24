#ifndef SPRITE_H
#define SPRITE_H

#include "SDL.h"
#include "component.h"

class Sprite : public Component {
  public:
    Sprite(class Actor* owner, int order = 100);
    ~Sprite();

    virtual void Draw(SDL_Renderer* renderer);
    virtual void SetTexture(SDL_Texture* text);

    int GetDrawOrder() const { return drawOrder; };
    int GetTextureWidth() const { return textureWidth; };
    int GetTextureHeight() const { return textureHeight; };

  protected:
    SDL_Texture* texture;
    int drawOrder;
    int textureWidth;
    int textureHeight;
};

#endif
