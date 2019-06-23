#ifndef GAME_H
#define GAME_H

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include "libsWin\glew\include\GL\glew.h"
#include "libsWin\glfw\include\GLFW\glfw3.h"
#include "libsWin\SDL2\i686-w64-mingw32\include\SDL2\SDL.h"
#else
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SDL2/SDL.h>
#endif

struct Vector2
{
  float x, y;
};

class Game
{
public:
  Game();
  bool Initialize();
  void RunLoop();
  void Shutdown();

private:
  void ProcessInput();
  void UpdateGame();
  void GenerateOutput();

  SDL_Window *mWindow;
  SDL_Renderer *mRenderer;
  Vector2 mPaddlePosU, mBallPos;
  Uint32 mTicksCount;
  SDL_DisplayMode DM;
  SDL_Event event;
  float deltaTime;
  bool mIsRunning;
  int screenHeight, screenWidth, thickness, paddleHeight;
  int mPaddleDir;
};

#endif
