#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include <unordered_map>
#include <string>
#include <vector>

class Game {
  public:
    Game();
    ~Game();

    bool Initialize();
    void Run();

    void AddActor(class Actor* actor);
    void AddSprite(class Sprite* sprite);

    void RemoveActor(class Actor* actor);
    void RemoveSprite(class Sprite* sprite);

    SDL_Texture* GetTexture(const std::string& fileName);

  private:
    void ProcessInput();
    void UpdateGame();
    void RenderOutput();
    void LoadData();
    void UnloadData();

    std::unordered_map<std::string, SDL_Texture*> textures;

    std::vector<class Actor*> actors;
    std::vector<class Actor*> pendingActors;

    std::vector<class Sprite*> sprites;

    bool isRunning;
    bool isUpdatingActors;
    SDL_Window* window;
    SDL_Renderer* renderer;
    Uint32 ticksCount;

    class Ship* ship;
};

#endif
