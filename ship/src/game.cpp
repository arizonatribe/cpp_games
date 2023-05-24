#include "SDL_image.h"
#include "bgsprite.h"
#include "game.h"
#include "math.h"
#include <algorithm>
#include "sprite.h"
#include "ship.h"
#include "actor.h"

Game::Game()
  : window(nullptr)
  , renderer(nullptr)
  , ticksCount(0)
  , isRunning(true)
  , isUpdatingActors(false)
{

}

Game::~Game() {
  UnloadData();
  IMG_Quit();
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
}

void Game::AddActor(Actor* actor) {
  if (isUpdatingActors) {
    pendingActors.emplace_back(actor);
  } else {
    actors.emplace_back(actor);
  }
}

void Game::RemoveActor(Actor* actor) {
  auto iter = std::find(pendingActors.begin(), pendingActors.end(), actor);
  if (iter != pendingActors.end()) {
    std::iter_swap(iter, pendingActors.end() - 1);
    pendingActors.pop_back();
  }
}

void Game::AddSprite(Sprite* sprite) {
  int drawOrder = sprite->GetDrawOrder();
  auto iter = sprites.begin();
  for (; iter != sprites.end(); ++iter) {
    if (drawOrder < (*iter)->GetDrawOrder()) {
      break;
    }
  }

  sprites.insert(iter, sprite);
}

void Game::RemoveSprite(Sprite* sprite) {
  auto iter = std::find(sprites.begin(), sprites.end(), sprite);
  sprites.erase(iter);
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
    SDL_Log("Unable to initialize SDL renderer: %s", SDL_GetError());
    return false;
  }

  if (IMG_Init(IMG_INIT_PNG) == 0) {
    SDL_Log("Unable to initialize SDL image: %s", SDL_GetError());
    return false;
  }

  LoadData();

  ticksCount = SDL_GetTicks();

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
    switch (e.key.keysym.sym) {
      case SDL_QUIT:
        isRunning = false;
        break;
      case SDLK_ESCAPE:
        isRunning = false;
        break;
    }
  }

  const Uint8* state = SDL_GetKeyboardState(NULL);
  ship->ProcessKeyboard(state);
}

void Game::RenderOutput() {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  for (auto sprite : sprites) {
    sprite->Draw(renderer);
  }

  SDL_RenderPresent(renderer);
}

void Game::LoadData() {
  ship = new Ship(this);
  ship->SetPosition(Vector2(100.0f, 384.0f));
  ship->SetScale(1.5f);

  Actor* temp = new Actor(this);
  temp->SetPosition(Vector2(512.0f, 384.0f));

  BGSprite* bg = new BGSprite(temp);
  bg->SetScreenSize(Vector2(1024.0f, 768.0f));
  std::vector<SDL_Texture*> bgTexts = {
    GetTexture("assets/back01.png"),
    GetTexture("assets/back02.png")
  };
  bg->SetBGTextures(bgTexts);
  bg->SetScrollSpeed(-100.0f);

  bg = new BGSprite(temp, 50);
  bg->SetScreenSize(Vector2(1024.0f, 768.0f));
  bgTexts = {
    GetTexture("assets/stars.png"),
    GetTexture("assets/stars.png")
  };
  bg->SetBGTextures(bgTexts);
  bg->SetScrollSpeed(-200.0f);
}

SDL_Texture* Game::GetTexture(const std::string& fileName) {
  SDL_Texture* tex = nullptr;
  auto iter = textures.find(fileName);
  if (iter != textures.end()) {
    tex = iter->second;
  } else {
    SDL_Surface* surf = IMG_Load(fileName.c_str());
    if (!surf) {
      SDL_Log("Failed to load texture file %s", fileName.c_str());
      return nullptr;
    }

    tex = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);
    if (!tex) {
      SDL_Log("Failed to convert surface to texture for file %s", fileName.c_str());
      return nullptr;
    }

    textures.emplace(fileName.c_str(), tex);
  }

  return tex;
}

void Game::UnloadData() {
  while (!actors.empty()) {
    delete actors.back();
  }

  for (auto i : textures) {
    SDL_DestroyTexture(i.second);
  }

  textures.clear();
}

void Game::UpdateGame() {
  while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksCount + 16))
    ;

  float deltaTime = (SDL_GetTicks() - ticksCount) / 1000.0f;

  if (deltaTime > 0.05f)
    deltaTime = 0.05f;

  ticksCount = SDL_GetTicks();

  isUpdatingActors = true;
  for (auto actor : actors) {
    actor->Update(deltaTime);
  }
  isUpdatingActors = false;

  for (auto actor : pendingActors) {
    actors.emplace_back(actor);
  }
  pendingActors.clear();

  std::vector<Actor*> deadActors;
  for (auto actor : actors) {
    if (actor->GetState() == Actor::Dead) {
      deadActors.emplace_back(actor);
    }
  }

  for (auto actor : deadActors) {
    delete actor;
  }
}
