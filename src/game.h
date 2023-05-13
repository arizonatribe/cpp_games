#ifndef GAME_H
#define GAME_H

#include "SDL.h"

struct Coordinates
{
  float x;
  float y;
};

class Game {
  public:
    Game();
    ~Game();

    bool Initialize();
    void Run();

  private:
    void ProcessInput();
    void UpdateGame();
    void RenderOutput();

    bool isRunning;
    SDL_Window* window;
    SDL_Renderer* renderer;
    Uint32 ticksCount;

    int paddleDir;
    Coordinates paddlePos;
    Coordinates ballPos;
    Coordinates ballVel;
};

#endif
