#ifndef GAME_H
#define GAME_H

#include "libsWin\glew\include\GL\glew.h"
#include "libsWin\glfw\include\GLFW\glfw3.h"
#include "libsWin\SDL2\i686-w64-mingw32\include\SDL2\SDL.h"

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

  static const int THICKNESS = 15;

  SDL_Window *mWindow;
  SDL_Renderer *mRenderer;
  Vector2 mPaddlePos, mBallPos;
  Uint32 mTicksCount;
  SDL_DisplayMode DM;
  SDL_Event event;
  float deltaTime;
  bool mIsRunning;
  int screenHeight;
  int screenWidth;
};

#endif