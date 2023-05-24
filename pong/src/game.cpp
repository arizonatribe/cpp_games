#include "game.h"

const int thickness = 15;
const float paddleH = 100.0f;

Game::Game() : window(nullptr), renderer(nullptr), ticksCount(0), isRunning(true), paddleDir(0) { }

Game::~Game() {
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
}

bool Game::Initialize() {
  int initResult = SDL_Init(SDL_INIT_VIDEO);

  if (initResult != 0) {
    SDL_Log("Unable to initialize SDL library: %s", SDL_GetError());
    return false;
  }

  window = SDL_CreateWindow("Pong", 0, 0, 1024, 768, 0);

  if (window == nullptr) {
    SDL_Log("Unable to initialize SDL window: %s", SDL_GetError());
    return false;
  }

  renderer = SDL_CreateRenderer(
    window,
    -1,
    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
  );

  if (renderer == nullptr) {
    SDL_Log("Unable to initialize SDL rendererz: %s", SDL_GetError());
    return false;
  }

  ballPos = Coordinates{
    .x = 1068.0f / 2.0f - thickness,
    .y = 768.0f / 2.0f - thickness,
  };
  paddlePos = Coordinates{
    .x = 10.0f,
    .y = 768.0f / 2.0f - thickness * 8,
  };
  ballVel = Coordinates{
    .x = -200.0f,
    .y = 235.0f,
  };

  return true;
}

void Game::Run() {
  while (isRunning) {
    ProcessInput();
    UpdateGame();
    RenderOutput();
  }
}

void Game::ProcessInput() {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    paddleDir = 0;

    switch (e.key.keysym.sym) {
      case SDL_QUIT:
        isRunning = false;
        break;
      case SDLK_ESCAPE:
        isRunning = false;
        break;
      case SDLK_w:
        paddleDir -=1;
        break;
      case SDLK_s:
        paddleDir += 1;
        break;
    }
  }
}

void Game::RenderOutput() {
  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
  SDL_RenderClear(renderer);

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_Rect topWall{0, 0, 1024, thickness};
  SDL_RenderFillRect(renderer, &topWall);
  SDL_Rect bottomWall{0, 768 - thickness, 1024, thickness};
  SDL_RenderFillRect(renderer, &bottomWall);
  SDL_Rect rightWall{1024 - thickness, 0, thickness, 1024};
  SDL_RenderFillRect(renderer, &rightWall);

  SDL_Rect ball{
    static_cast<int>(ballPos.x - thickness / 2),
    static_cast<int>(ballPos.y - thickness / 2),
    thickness,
    thickness,
  };
  SDL_RenderFillRect(renderer, &ball);

  SDL_Rect paddle{
    static_cast<int>(paddlePos.x),
    static_cast<int>(paddlePos.y - paddleH / 2),
    thickness,
    static_cast<int>(paddleH),
  };
  SDL_RenderFillRect(renderer, &paddle);

  SDL_RenderPresent(renderer);
}

void Game::UpdateGame() {
  while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksCount + 16))
    ;

  float deltaTime = (SDL_GetTicks() - ticksCount) / 1000.0f;

  if (deltaTime > 0.05f)
    deltaTime = 0.05f;

  ticksCount = SDL_GetTicks();

  if (paddleDir != 0) {
    paddlePos.y += paddleDir * 300.0f * deltaTime;

    if (paddlePos.y < (paddleH / 2.0f + thickness)) {
      paddlePos.y = paddleH / 2.0f + thickness;
    } else if (paddlePos.y > (768.0f - paddleH / 2.0f - thickness)) {
      paddlePos.y = 768.0f - paddleH / 2.0f - thickness;
    }
  }

  ballPos.x += ballVel.x * deltaTime;
  ballPos.y += ballVel.y * deltaTime;

  float diff = paddlePos.y - ballPos.y;
  diff = (diff > 0.0f) ? diff : -diff;

  if (diff <= paddleH / 2.0f && ballPos.x <= 25.0f && ballPos.x >= 20.0f && ballVel.x < 0.0f)
    ballVel.x *= -1.0f;
  else if (ballPos.x <= 0.0f)
    isRunning = false;
  else if (ballPos.x >= (1024.0f - thickness) && ballVel.x > 0.0f)
    ballVel.x *= -1.0f;
  else if (ballPos.y <= thickness && ballVel.y < 0.0f)
    ballVel.y *= -1;
  else if (ballPos.y >= (768 - thickness) && ballVel.y > 0.0f)
    ballVel.y *= -1;
}
