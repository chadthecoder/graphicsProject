#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "Game.hpp"

int SDL_main(int argc, char *argv[])
{
  Game game;

  bool success = game.Initialize();
  if (success)
  {
    game.RunLoop();
  }
  game.Shutdown();
  return 0;
}