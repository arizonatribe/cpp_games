#include "game.h"

int main()
{
  Game game;
  bool success = game.Initialize();
  if (success) game.Run();
  return 0;
}
